#include "computer.h"

int main(){
	ExpressionManager expMng;
	Pile expAff;
	Controleur controleur(expMng,expAff);
	expAff.setMessage("Bienvenue");
	controleur.executer();
	return 0;
}


