#include "datos.h"
#include "ui_datos.h"
#include <QDebug>
#include <QMessageBox>

Datos::Datos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Datos)
{
    ui->setupUi(this);
}

Datos::~Datos()
{
    delete ui;
}

void Datos::on_pushButton_clicked()
{
    insertarUsuario();
    this->hide();
}

void Datos::insertarUsuario()
{
    //Agregamos un registro
    QString consulta;
    consulta.append("INSERT INTO  usuarios  (   "
                    "planta ,"
                    "t_max ,"
                    "t_min ,"
                    "nivel_riego, "
                    "nivel_luz ,"
                    "precaucion)"
                    "VALUES("
                    "  '"+ ui->lineEdit_planta->text()   +  "'  , " //Toma los datos del lineedit
                    "  '"+ ui->lineEdit_t_max->text() +  "'  , "
                    "  '"+ ui->lineEdit_t_min->text()     +  "'  , "
                    "  '"+ ui->lineEdit_nivel_riego->text()    +  "' ,   "
                    "  '"+ ui->lineEdit_nivel_luz->text()     +  "'  , "
                     "  '"+ ui->lineEdit_precaucion->text()    +  "'    "
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

void Datos::on_pushButton_2_clicked()
{
    this->hide();
}
