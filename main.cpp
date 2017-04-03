#include <QApplication>
#include "myWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myWindow myWin; //Ajout de notre classe myWindow
    myWin.show();   //Exécution de notre fenêtre de rendu OpenGL
    myWin.setFixedSize(SIZE,SIZE);
    return app.exec();
}
