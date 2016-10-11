#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class ComputerException {
	string info;
public:
	ComputerException(const string& str):info(str){}
	string getInfo() const { return info; }
};

class Expression {
	int value;
public:
	Expression(int v):value(v){}
	string toString() const;
	int getValue() const { return value; }
};



class ExpressionManager {
	static ExpressionManager* instance;
	Expression** exps;
	unsigned int nb;
	unsigned int nbMax;
	void agrandissementCapacite();
	ExpressionManager():exps(0),nb(0),nbMax(0){}
	~ExpressionManager();
	ExpressionManager(const ExpressionManager& m);
	ExpressionManager& operator=(const ExpressionManager& m);
public:
	Expression& addExpression(int v);
	void removeExpression(Expression& e);
	static ExpressionManager& donneInstance();
	static void libereInstance();

	class Iterator
	{
		Expression ** currentExp;
		unsigned int nbRemain;
		Iterator(Expression** u, unsigned int nb):currentExp(u),nbRemain(nb){}
		friend class ExpressionManager;
	public:
		bool isDone() const {return nbRemain==0;}
		void next(){
			if (isDone())
			{
				throw ComputerException("erreur");
			}
			nbRemain--;
			currentExp++;
		};
		Expression& current() const {
			if (isDone())	
			{
				throw ComputerException("erreur");
			}
			return **currentExp;
		}
	};
	Iterator getIterator(){
		return Iterator(exps,nb);
	}
};


class Item {
	Expression* exp;
public:
	Item():exp(0){}
	void setExpression(Expression& e) { exp=&e; }
	void raz() { exp=0; }
	Expression& getExpression() const;
};

class Pile {
	Item* items;
	unsigned int nb;
	unsigned int nbMax;
	string message;
	void agrandissementCapacite();
	unsigned int nbAffiche;
public:
	Pile():items(0),nb(0),nbMax(0),message(""),nbAffiche(4){}
	~Pile();
	void push(Expression& e);
	void pop();
	bool estVide() const { return nb==0; }
	unsigned int taille() const { return nb; }
	void affiche() const;
	Expression& top() const;
	unsigned int getNbItemsToAffiche()const { return nbAffiche; }
	void setNbItemsToAffiche(unsigned int n) { nb=n; }
	void setMessage(const string& m) { message=m; }
	string getMessage() const { return message; }
};

class Controleur {
	ExpressionManager& expMng;
	Pile& expAff;
public:
	Controleur(ExpressionManager& m, Pile& v):
		expMng(m), expAff(v){}
	void commande(const string& c);
	void executer();
};


#endif