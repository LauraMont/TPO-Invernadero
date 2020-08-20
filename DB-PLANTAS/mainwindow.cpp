#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Creacion de la base de datos...
    qDebug()<<"Aplicacion iniciada...";
    QString  nombre;
    nombre.append("badeDeDatos1.sqlite");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombre);
    if(db.open())  {
        qDebug()<<"Se ha conectado a la base de datos.";
    }
    else{
        qDebug()<<"ERROR! No se ha conectado a la base de datos.";
    }

    CrearTablaUsuarios();
    mostrarDatos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CrearTablaUsuarios()
{
    //Creacion de tabla...
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS   usuarios  (   "
                    "id INTEGER PRIMARY KEY AUTOINCREMENT ,"
                    "nombre VARCHAR(100),"
                    "apellido VARCHAR(100),"
                    "edad INTEGRER NOT NULL,"
                    "clase INTEGRER NOT NULL"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

   if( crear.exec()   ){            //Devuelte un booleano
       qDebug()<<"La tabla usuarios existe o se ha creado correctamente";
   }
   else{
       qDebug()<<"ERROR!"<<crear.lastError();
   }
}

void MainWindow::insertarUsuario()
{
    //Agregamos un registro
    QString consulta;
    consulta.append("INSERT INTO  usuarios  (   "
                    "nombre,"
                    "apellido ,"
                    "edad ,"
                    "clase )"
                    "VALUES("
                    "    '     "+ ui->lineEdit_Nombre->text()+"     ' ,     "               //Toma los datos del lineedit
                     "   '     "+ ui->lineEdit_Apellido->text()+"     ',    "
                    "        "+ ui->lineEdit_Edad->text()+"   ,   "
                    "          "+ ui->lineEdit_Clase->text()+"    "
                    ");");
    QSqlQuery insertar;
    insertar.prepare(consulta);

   if( insertar.exec()   ){            //Devuelte un booleano
       qDebug()<<"El usuario existe o se ha insertado correctamente";
   }
   else{
       qDebug()<<"El usuario NO existe o NO se ha insertado correctamente";
       qDebug()<<"ERROR!"<<insertar.lastError();
   }
}

void MainWindow::mostrarDatos()
{
    //Mostramos los datos...
    QString consulta;
    consulta.append("SELECT * FROM  usuarios");

    QSqlQuery consultar;
    consultar.prepare(consulta);

   if( consultar.exec()   ){            //Devuelte un booleano
       qDebug()<<"Se ha consultado correctamente";
   }
   else{
       qDebug()<<"No se ha consultado correctamente";
       qDebug()<<"ERROR!"<<consultar.lastError();
   }
   int fila=0;

   ui->tableWidget_Datos->setRowCount(0);
   while(consultar.next()){ //hasta que el string este vacio
       ui->tableWidget_Datos->insertRow(fila);                //Agrego una fila

       ui->tableWidget_Datos->setItem(fila , 0 ,new QTableWidgetItem(consultar.value(1).toByteArray().constData()) );
       ui->tableWidget_Datos->setItem(fila , 1 ,new QTableWidgetItem(consultar.value(2).toByteArray().constData()) );
       ui->tableWidget_Datos->setItem(fila , 2 ,new QTableWidgetItem(consultar.value(3).toByteArray().constData()) );
       ui->tableWidget_Datos->setItem(fila , 3 ,new QTableWidgetItem(consultar.value(4).toByteArray().constData()) );

       fila++;
   }
}


void MainWindow::on_pushButton_Agregar_clicked()
{
    insertarUsuario();
    mostrarDatos();
}
