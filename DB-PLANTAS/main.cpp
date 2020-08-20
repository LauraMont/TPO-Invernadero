#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/**
        Observaciones:
        *Agregar la opcion de eliminar datos
        *Agregar la opcion de modificar datos
        *Cambiar la ubicacion de la base de datos ,preferiblemente dentro de una carpeta (crear todo si no existe)
**/
