#include "computer.h"
#include <algorithm>
#include <cstdlib>

string  Expression::toString() const {
	stringstream s;
	s<<value;
	return s.str();
}

ExpressionManager* ExpressionManager::instance=nullptr;

ExpressionManager& ExpressionManager::donneInstance(){
	if (instance==nullptr)
	{
		instance=new ExpressionManager;		
	}
	return *instance;
}

void ExpressionManager::libereInstance(){
	if (instance!=0)
	{
		delete instance;
	}
	instance=nullptr;
}

void ExpressionManager::agrandissementCapacite() {
	Expression** newtab=new Expression*[(nbMax+1)*2];
	//for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
	std::memcpy(newtab,exps,nb*sizeof(Expression*));
	Expression**  old=exps;
	exps=newtab;
	nbMax=(nbMax+1)*2;
	delete old;
}

Expression& ExpressionManager::addExpression(int v){
	if (nb==nbMax) agrandissementCapacite();
	exps[nb++]=new Expression(v);
	return *exps[nb-1];
}

void ExpressionManager::removeExpression(Expression& e){
	unsigned int i=0;
	while(i<nb && exps[i]!=&e) i++;
	if (i==nb) throw ComputerException("elimination d'une Expression inexistante");
	delete exps[i];
	i++;
	while(i<nb) { exps[i-1]=exps[i]; i++; }
	nb--;
}

ExpressionManager::~ExpressionManager(){
	for(unsigned int i=0; i<nb; i++) delete exps[i];
	delete[] exps;
}


ExpressionManager::ExpressionManager(const ExpressionManager& m):
	exps(new Expression*[m.nbMax]), nb(m.nb), nbMax(m.nbMax)
{
	for(unsigned int i=0; i<nb; i++) 
		exps[i]=new Expression(*m.exps[i]);
}

ExpressionManager& ExpressionManager::operator=(const ExpressionManager& m){
	if (this==&m) return *this;
	Expression** newtab=new Expression*[m.nbMax];
	for(unsigned int i=0; i<nb; i++) 
		newtab[i]=new Expression(*m.exps[i]);
	Expression** old=exps;
	unsigned int oldnb=nb;
	exps=newtab;
	nb=m.nb;
	nbMax=m.nbMax;
	for(unsigned int i=0; i<oldnb; i++) delete old[i];
	delete[] old;
	return *this;
}

Expression& Item::getExpression() const{ 
		if (exp==0) throw ComputerException("Item : tentative d'acces a une expression inexistante"); 
		return *exp; 
}


void Pile::agrandissementCapacite() {
	Item* newtab=new Item[(nbMax+1)*2];
	for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
	Item*  old=items;
	items=newtab;
	nbMax=(nbMax+1)*2;
	delete[] old;
}

void Pile::push(Expression& e){
	if (nb==nbMax) agrandissementCapacite();
	items[nb].setExpression(e);
	nb++;
}

void Pile::pop(){
	nb--;
	items[nb].raz();
}

void Pile::affiche() const{
	system("cls");
	cout<<"********************************************* \n";
	cout<<"M : "<<message<<"\n";
	cout<<"---------------------------------------------\n";
	for(int i=nbAffiche; i>0; i--) {
		if (i<=static_cast<int>(nb)) cout<<i<<": "<<items[nb-i].getExpression().toString()<<"\n";
		else cout<<i<<": \n"; 
	}
	cout<<"---------------------------------------------\n";
}


Pile::~Pile(){
	delete[] items;
}

Expression& Pile::top() const { 
	
	if (nb==0) throw ComputerException("aucune expression sur la pile");
	return items[nb-1].getExpression(); 
}
	


bool estUnOperateur(const string& s){
	if (s=="+") return true;
	if (s=="-") return true;
	if (s=="*") return true;
	if (s=="/") return true;
	return false;
}

bool estUnNombre(const string& s){
	unsigned int i=0;
	//for(i=0; i<s.size(); i++)
		//if (s[i]<'0' || s[i]>'9') return false;
	for(string::const_iterator it=s.begin(); it!=s.end(); ++it)
		if (*it<'0' || *it>'9') return false;
	return true;
}


void Controleur::commande(const string& c){
	if (estUnNombre(c)){
		expAff.push(expMng.addExpression(atoi(c.c_str())));
	}else{
		
		if (estUnOperateur(c)){
			if (expAff.taille()>=2) {
				int v2=expAff.top().getValue();
				expMng.removeExpression(expAff.top());
				expAff.pop();
				int v1=expAff.top().getValue();
				expMng.removeExpression(expAff.top());
				expAff.pop();
			
				int res;
				if (c=="+") res=v1+v2;
				if (c=="-") res=v1-v2;
				if (c=="*") res=v1*v2;
				if (c=="/") {
					if (v2!=0) 	res=v1/v2;
					else{
						expAff.setMessage("Erreur : division par zero");
						// restauration de la pile
						expAff.push(expMng.addExpression(v1));
						res=v2;
					}
				}
				Expression& e=expMng.addExpression(res);
				expAff.push(e);
			}else{
				expAff.setMessage("Erreur : pas assez d'arguments");
			}
		}else expAff.setMessage("Erreur : commande inconnue");
	}
}

void Controleur::executer(){
	string c;
	do {
		expAff.affiche();
		cout<<"?-";
		cin>>c;
		if (c!="Q") commande(c);
	}while(c!="Q");
}