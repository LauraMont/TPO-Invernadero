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
    ui->lineEdit_h_amb->setValidator( new QIntValidator(0, 99, this) );
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
bool Datos::insertarPlanta()
{
    QSqlQuery insertar;
    QString consulta;
    bool repetido;
    bool insertada = true;
    repetido = YaExiste(ui->lineEdit_planta->text()); //Corroboro que el nombre de la planta no se repita
    if(!repetido)
    {
        consulta.append("INSERT INTO  plantas  (   "
                        "planta ,"
                        "temp_max ,"
                        "temp_min ,"
                        "hum_tierra,"
                        "hum_amb,"
                        "precaucion,"
                        "ruta_imagen )"
                        "VALUES("//Toma los datos del lineedit
                        "  '"+ ui->lineEdit_planta->text()      + "' , "
                        "  '"+ ui->lineEdit_t_max->text()       + "' , "
                        "  '"+ ui->lineEdit_t_min->text()       + "' , "
                        "  '"+ ui->lineEdit_h_tierra->text()    + "' , "
                        "  '"+ ui->lineEdit_h_amb->text()       + "' , "
                        "  '"+ ui->lineEdit_precaucion->text()  + "' , "
                        "  '"+ ui->lineEdit_foto->text()        + "'   "
                        ")");

       insertar.prepare(consulta);

       if(insertar.exec())//Devuelve un booleano
           qDebug()<<"Se agrego una planta";
       else
       {
           qDebug()<<"NO se ha podido agregar la planta";
           qDebug()<<"ERROR!"<<insertar.lastError();
       }

    }
    else
    {
        insertar.clear();
        insertada = false;
        QMessageBox::critical(this,"Error", "Nombre de planta repetido");
    }
    return insertada;
}

bool Datos::YaExiste(QString nombre)
{
    QSqlQuery consultar, cantidad;
    QString planta;
    int cant;
    bool repetido;
    consultar.prepare("SELECT planta FROM plantas ORDER by planta ASC");
    cantidad.prepare("SELECT COUNT(*) FROM plantas");//Cuento cuantas hay

    if(!consultar.exec() || !cantidad.exec()) //Devuelve un booleano
        qDebug()<<"ERROR EN LA CONSULTA!"<< consultar.lastError() << cantidad.lastError();

    cantidad.next();
    cant = cantidad.value(0).toInt();//Cantidad de registros en la base
    while(consultar.next())//hasta que el string este vacio
    {
        for (int i=0; i<cant; i++)
        {
            planta = consultar.value(i).toString();//Elemento leido de la BD
            if(planta.length())
                    if(nombre == planta)
                        repetido = true;
        }
      //La consulta devuelve valores en blanco, por eso chequeo la longitud y
    }
    return repetido;
}
/**
    \fn  	void Datos::on_pushButton_clicked()
    \brief  Slot del botón de agregar planta clickeado
*/
void Datos::on_pushButton_clicked()
{
    bool insertada = false;
    insertada = insertarPlanta();
    if(insertada)
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
//    qDebug() << String_PathFoto  << String_PathFoto.length() << endl;

}
