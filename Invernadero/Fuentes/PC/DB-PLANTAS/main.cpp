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
   *Adaptar los datos (variables y campos que usaremos para las plantas) a nuestro proyecto -Pendiente: Ana
   *Adaptar el programa al tamaño que tenga -Hecho: Javier
   *Embellecer la funcion de modificar datos -Pendiente: Nico T
   *Cambiar la ubicacion de la base de datos, preferiblemente dentro de una carpeta (crear todo si no existe)  -Hecho: Nico T
   *Ir agregando prototipos de plantas -Pendiente: Nico P
**/
