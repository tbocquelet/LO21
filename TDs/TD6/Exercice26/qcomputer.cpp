#include <qcomputer.h>

QComputer::QComputer(QWidget* parent):QWidget(parent){
    message=new QLineEdit(this); // afficher les messages vers l'utilisateur
    pile=new Pile(); // gérer les expressions impilées
// on veut autant de lignes que l'on a de lignes dans la pile affichée
    vuePile=new QTableWidget(pile->getNbItemsToAffiche(),1,this); // afficher l'état de la pile
// vuePile=new QTableWidget(nbLignes,nbColonnes,this);
    commande=new QLineEdit(this); // saisir les commandes de l'utilisateur
    couche=new QVBoxLayout; // aligner les 3 précédents widgets
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    setLayout(couche);

// interprète les commandes de l'utilisateur
    controleur=new Controleur(ExpressionManager::getInstance(),*pile);

    setWindowTitle("UTComputer");
// rend la barre accessible uniquement en lecture
    message->setReadOnly(true);
    message->setText("Bienvenue");
    message->setStyleSheet("background:blake; color:white");

    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);
    QStringList nombres;
    for (int i=pile->getNbItemsToAffiche(); i>0;i--) {
        QString str=QString::number(i);
        str+=" :";
        nombres<<str;
    }
    vuePile->setVerticalHeaderLabels(nombres);
// rendre le QTableWidget inéditqble
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(commande, SIGNAL(returnPressed()),this,SLOT(getNextCommande())
);

// modification état émis lorsqu'un élément est ajouté ou retiré de la pile
    connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));

    for (unsigned int i = 0; i < pile->getNbItemsToAffiche(); i++) {
        vuePile->setItem(i,0,new QTableWidgetItem(""));
    }
}

void QComputer::refresh(){
// mise à jour du message
    message->setText(pile->getMessage());
// mise à jour de la pile
    for (unsigned int i = 0; i < pile->getNbItemsToAffiche(); i++) {
        vuePile->item(i,0)->setText("");
    }
    unsigned int nb=0; // compteur
    for(Pile::iterator it=pile->begin(); it!=pile->end() && nb<pile->getNbItemsToAffiche();++it){
       vuePile->item(pile->getNbItemsToAffiche()-nb-1,0)->setText((*it).toString());
       nb++;
    }
}

void QComputer::getNextCommande(){
    pile->setMessage("");
    controleur->commande(commande->text());
    commande->clear();
}

