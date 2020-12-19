#include "datos.h"
#include "ui_datos.h"

extern QString rutaFotos;

/**
    \fn  	Datos::Datos(QWidget *parent)
    \brief	Constructor
*/
Datos::Datos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Datos)
{
    ui->setupUi(this);
    ui->lineEdit_foto->setEnabled(false);
    ui->lineEdit_t_min->setValidator( new QIntValidator(0, 99, this) );
    ui->lineEdit_t_max->setValidator( new QIntValidator(0, 99, this) );
    ui->lineEdit_h_tierra->setValidator( new QIntValidator(0, 99, this) );
    ui->lineEdit_h_amb->setValidator(new QIntValidator(0,99,this));
    ui->lineEdit_nivel_riego->setValidator( new QIntValidator(0, 9, this) );
}

/**
    \fn  	Datos::~Datos()
    \brief	Destructor
*/
Datos::~Datos()
{
    delete ui;
}

/**
    \fn  	void Datos::insertarPlanta()
    \brief  Instera una uneva planta en la base de datos leyendo los line edit
*/
void Datos::insertarPlanta()
{
    //Agregamos un registro
    QString consulta;
    consulta.append("INSERT INTO  plantas  (   "
                    "planta ,"
                    "temp_max ,"
                    "temp_min ,"
                    "hum_tierra,"
                    "hum_amb,"
                    "nivel_riego,"
                    "precaucion,"
                    "ruta_imagen )"
                    "VALUES("//Toma los datos del lineedit
                    "  '"+ ui->lineEdit_planta->text()      + "' , "
                    "  '"+ ui->lineEdit_t_max->text()       + "' , "
                    "  '"+ ui->lineEdit_t_min->text()       + "' , "
                    "  '"+ ui->lineEdit_h_tierra->text()    + "' , "
                    "  '"+ ui->lineEdit_h_amb->text()       + "' , "
                    "  '"+ ui->lineEdit_nivel_riego->text() + "' , "
                    "  '"+ ui->lineEdit_precaucion->text()  + "' , "
                    "  '"+ ui->lineEdit_foto->text()        + "'   "
                    ")");
   QSqlQuery insertar;
   insertar.prepare(consulta);
   if(insertar.exec())//Devuelve un booleano
       qDebug()<<"El usuario existe o se ha insertado correctamente";
   else{
       qDebug()<<"El usuario NO existe o NO se ha insertado correctamente";
       qDebug()<<"ERROR!"<<insertar.lastError();
   }
}

/**
    \fn  	void Datos::on_pushButton_clicked()
    \brief  Slot del botón de agregar planta clickeado
*/
void Datos::on_pushButton_clicked()
{
    insertarPlanta();
    this->hide();
}

/**
    \fn  	void Datos::on_pushButton_2_clicked()
    \brief  Slot del botón de cancelar clickeado
*/
void Datos::on_pushButton_2_clicked()
{
    this->hide();
}

/**
    \fn  	void Datos::on_pushButton_3_clicked()
    \brief  Carga en el line edit la dirección de la imagen seleccionada
*/
void Datos::on_pushButton_3_clicked()
{
    QString String_PathFoto = QFileDialog::getOpenFileName(this, "Select a file to open...", rutaFotos);
    ui->lineEdit_foto->setText(String_PathFoto);
    ui->lineEdit_foto->setEnabled(true);
    qDebug() << String_PathFoto  << String_PathFoto.length() << endl;

}
