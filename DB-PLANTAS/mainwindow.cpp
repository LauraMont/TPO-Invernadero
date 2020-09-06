#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Creacion de la base de datos...
    qDebug()<<"Aplicacion iniciada...";
    QString  nombre;
    nombre.append("baseDeDatos1.sqlite");
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
    if(!crear.prepare(consulta))
    {
        QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta de nombres");
    }
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
                    "  '"+ ui->lineEdit_Nombre->text()   +  "'  , " //Toma los datos del lineedit
                    "  '"+ ui->lineEdit_Apellido->text() +  "'  , "
                    "  '"+ ui->lineEdit_Edad->text()     +  "'  , "
                    "  '"+ ui->lineEdit_Clase->text()    +  "'    "
                    ");");

    QSqlQuery insertar;
    insertar.prepare(consulta);

   if(insertar.exec())//Devuelve un booleano
   {
       qDebug()<<"El usuario existe o se ha insertado correctamente";
   }
   else{
       qDebug()<<"El usuario NO existe o NO se ha insertado correctamente";
       qDebug()<<"ERROR!"<<insertar.lastError();
   }
}

void MainWindow::mostrarDatos()
{
    int fila=0;

    //Mostramos los datos...
    QString consulta;
    consulta.append("SELECT * FROM  usuarios");

    QSqlQuery consultar(db);
    consultar.prepare(consulta);

   if( consultar.exec()   ){            //Devuelve un booleano
       qDebug()<<"Se ha consultado correctamente";
   }
   else{
       qDebug()<<"No se ha consultado correctamente";
       qDebug()<<"ERROR!"<<consultar.lastError();
   }

   ui->tableWidget_Datos->setRowCount(0);
   while(consultar.next())//hasta que el string este vacio
   {
       ui->tableWidget_Datos->insertRow(fila);//Agrego una fila

       for (int i=0; i<5; i++)
       {
            ui->tableWidget_Datos->setItem(fila , i ,
            new QTableWidgetItem(consultar.value(i/*+1*/).toByteArray().constData()) );
       }
       fila++;
   }
}


void MainWindow::on_pushButton_Agregar_clicked()
{
    insertarUsuario();
    mostrarDatos();
    ui->lineEdit_Nombre->clear();
    ui->lineEdit_Nombre->echoMode();
    ui->lineEdit_Nombre->setText("Nombre");
//    ui->lineEdit_Nombre->setPlaceholderText();





//    ui->lineEdit_Apellido->clear();
//    ui->lineEdit_Edad->clear();
//    ui->lineEdit_Clase->clear();

}

void MainWindow::on_tableWidget_Datos_cellClicked(int row, int column)
{
   if (isEnabled) {
       ui->pushButton_Borrar->setEnabled(isEnabled=false);
   }
   else {
        ui->pushButton_Borrar->setEnabled(isEnabled=true);
   }
}

void MainWindow::on_pushButton_Borrar_clicked()
{
    int n=ui->tableWidget_Datos->selectionModel()->currentIndex().row();
    int id = ui->tableWidget_Datos->item(n,0)->text().toInt();
    //Obtiene el valor de la celda seleccionada que es el id de la db

    QString consulta("DELETE FROM usuarios WHERE id = ");
    consulta.append(QString::number(id));

    QSqlQuery consultar(db);
    consultar.prepare(consulta);

   if(consultar.exec())//Devuelve un booleano
   {
       qDebug()<<"Se borro con exito" << id;
       ui->tableWidget_Datos->removeRow(ui->tableWidget_Datos->selectionModel()->currentIndex().row());
   }
   else{
       qDebug()<<"No se pudo eliminar";
       qDebug()<<"ERROR!"<<consultar.lastError();
       QMessageBox::critical(NULL,"Error","No se pudo borrar el elemento seleccionado");
   }

}
void MainWindow::on_tableWidget_Datos_cellDoubleClicked(int row, int column)
{
    ui->pushButton_Guardar->setEnabled(true);
    fila = row;
    columna = column;
}

void MainWindow::on_pushButton_Guardar_clicked()
{
    QString value = ui->tableWidget_Datos->item(fila, columna)->text();//Obtengo el contenido de la celda
    int ID = ui->tableWidget_Datos->item(fila,0)->text().toInt();//Obtengo el id

    QSqlQuery qry;
    qry.prepare( "UPDATE usuarios SET apellido = 'Johnson' WHERE id = 8" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Updated!" );
    ui->pushButton_Guardar->setEnabled(false);
}
