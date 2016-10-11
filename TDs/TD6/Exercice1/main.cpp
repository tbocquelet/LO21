
#include <QApplication>
#include <QPushButton>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);// on cree un objet app de type QApplication
    QPushButton bouton("Quitter");
    bouton.show(); // montre le bouton
    QPushButton bouton2("Coucou");
    QObject::connect(&bouton,SIGNAL(clicked()),&app,SLOT(quit())); // méthode static de la classe QObject
    bouton2.show(); // créé un deuxième bouton
    return app.exec();/* exec démarre la boucle d'évènements permettant
d'intéragir avec l'application*/
}
