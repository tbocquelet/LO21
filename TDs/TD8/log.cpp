#include "log.h"

void MyLog::addEvt (const TIME::Date& d, const TIME::Horaire& h, const std::string& s) {
	// appel a l'operateur d'insertion de la classe Agenda
	if (begin()!=end())
	{
		// recuperation du dernier evenement
		const TIME::Evt1jDur & lastEvent=dynamic_cast<const TIME::Evt1jDur &>(*(--end()));
		// compare les dates et renvoie une exception si incoherence
		if (d<lastEvent.getDate()||(d==lastEvent.getDate() && h<lastEvent.getHoraire()))		
		{
			// 
			throw LogError("addition of a posterior event");
		}
	}
	*this<<TIME::Evt1jDur(d,s,h,TIME::Duree(0));
}

// Downcast 
// Cast implicite d'un pointeur/reference sur un objet d'une classe de base vers un pointeur/reference sur un objet d'une classe derivee pas autorise
// Downcast explicite est autorise
// dans le cas de methodes virutelles il faut faire un downcast 
// dynamic_cast a utiliser dans le cas du polymorphisme 
// prend en parametre une reference ou un pointeur
// effectue un controle de type a l'execution
// renvoie null si incompatibilite de type et parametre de type pointeur
// renvoie bad_cast si incompatibilite de type et parametre de type reference

void MyLog::displayLog(std::ostream& f) const {
	for(TIME::Agenda::iterator it=begin(); it!=end(); ++it){
		f<<dynamic_cast<const TIME::Evt1jDur&>(*it).getDate()<< " : "<<(*it).getDescription()<<std::endl;
	}
}

void MyLog2::addEvt (const TIME::Date& d, const TIME::Horaire& h, const std::string& s) {
	// appel a l'operateur d'insertion de la classe Agenda
	evts<<TIME::Evt1jDur(d,s,h,TIME::Duree(0));
}

void MyLog2::displayLog(std::ostream& f) const {
	for(TIME::Agenda::iterator it=evts.begin(); it!=evts.end(); ++it){
		f<<dynamic_cast<const TIME::Evt1jDur&>(*it).getDate()<< " : "<<(*it).getDescription()<<std::endl;
	}
}