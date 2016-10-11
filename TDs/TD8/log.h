#if !defined(LOG_H) 
#define LOG_H 

#include "timing.h" 
#include <iostream> 
#include "evenement.h"
#include <exception>


class Log {
public:
	virtual void addEvt(const TIME::Date& d, const TIME::Horaire& h, const std::string& s)=0;
	virtual void displayLog(std::ostream& f) const=0;
};


// adaptateur de classe : utilise l'heritage multiple
// les methodes de la classe agenda seront utilisables depuis la classe MyLog tout en etant invisibles (private) 
// a tout utilisateur de la classe MyLog ou dans toute classe derivee de MyLog

class MyLog : public Log, public TIME::Agenda{
public:
	void addEvt(const TIME::Date& d, const TIME::Horaire& h, const std::string& s);
	void displayLog(std::ostream& f) const;
};

// interface objectif : Log
// interface à adapter : Agenda

// adaptateur d'objet : utilise la composition 
class MyLog2 : public Log{
private:
	TIME::Agenda evts;
public:
	void addEvt(const TIME::Date& d, const TIME::Horaire& h, const std::string& s);
	void displayLog(std::ostream& f) const;
};


class LogError: public std::exception {
	std::string info; // description de l'exception
public:
	LogError(const char * s) throw() : info(s) {} // throw empêche de lever des exceptions
	const char * what() const throw() { return info.c_str(); }
	~LogError() throw() {}
};

#endif