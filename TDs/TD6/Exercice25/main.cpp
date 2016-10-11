#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;
    fenetre.setFixedSize(200, 200);
// objet commande
    QLineEdit commande(&fenetre); // &fenetre indique que fenetre est parent de line
// donc line sera intégré dans la fenêtre directement
    commande.move(10,10);
    commande.setFixedWidth(180);

// QUESTION 1
//    QPushButton un("1",&fenetre);
//    QPushButton deux("2",&fenetre);
//    QPushButton trois("3",&fenetre);
//    QPushButton quatre("4",&fenetre);
//// taille des boutons
//    un.setFixedSize(30,30);
//    deux.setFixedSize(30,30);
//    trois.setFixedSize(30,30);
//    quatre.setFixedSize(30,30);
//// position des boutons, c'est nous qui la définissons
//    un.move(10,45);
//    deux.move(45,45);
//    trois.move(80,45);
//    quatre.move(10,80);

// QUESTION 2
    QPushButton un("1",&fenetre);
    QPushButton deux("2",&fenetre);
    QPushButton trois("3",&fenetre);
    QPushButton quatre("4",&fenetre);
    QPushButton cinq("5",&fenetre);
    QPushButton six("6",&fenetre);
    QPushButton sept("7",&fenetre);
    QPushButton huit("8",&fenetre);
    QPushButton neuf("9",&fenetre);
    QPushButton zero("0",&fenetre);
    QPushButton plus("+",&fenetre);
    QPushButton moins("-",&fenetre);
    QPushButton mult("*",&fenetre);
    QPushButton div("/",&fenetre);
    QPushButton entree("Entrée",&fenetre);

    un.setFixedSize(30,30);
    deux.setFixedSize(30,30);
    trois.setFixedSize(30,30);
    quatre.setFixedSize(30,30);
    cinq.setFixedSize(30,30);
    six.setFixedSize(30,30);
    sept.setFixedSize(30,30);
    huit.setFixedSize(30,30);
    neuf.setFixedSize(30,30);
    zero.setFixedSize(30,30);
    entree.setFixedHeight(40);

    QHBoxLayout line1;
    line1.addWidget(&un);
    line1.addWidget(&deux);
    line1.addWidget(&trois);

    QHBoxLayout line2;
    line2.addWidget(&quatre);
    line2.addWidget(&cinq);
    line2.addWidget(&six);

    QHBoxLayout line3;
    line3.addWidget(&sept);
    line3.addWidget(&huit);
    line3.addWidget(&neuf);

    QVBoxLayout pave;
    pave.addLayout(&line1);
    pave.addLayout(&line2);
    pave.addLayout(&line3);
    pave.addWidget(&zero);

    QVBoxLayout ops;
    ops.addWidget(&plus);
    ops.addWidget(&moins);
    ops.addWidget(&mult);
    ops.addWidget(&div);
    ops.addWidget(&entree);

    QHBoxLayout interface;
    interface.addLayout(&pave);
    interface.addLayout(&ops);

    QVBoxLayout layout;
    layout.addWidget(&commande);
    layout.addLayout(&interface);

    fenetre.setLayout(&layout);
    fenetre.show();

    return app.exec();
}


