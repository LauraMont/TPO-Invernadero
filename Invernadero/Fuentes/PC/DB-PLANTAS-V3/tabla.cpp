#include "tabla.h"
#include "ui_tabla.h"

extern QSqlDatabase db;
extern bool huboCambios;

/**
    \fn  	Tabla::Tabla(QWidget *parent)
    \brief	Constructor
*/
Tabla::Tabla(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tabla)
{
    ui->setupUi(this);
    MostrarDatos();
}

/**
    \fn  	Tabla::~Tabla()
    \brief	Destructor
*/
Tabla::~Tabla()
{
    delete ui;
}

/**
    \fn  	mostrarDatos()
    \brief	Muestra el contenido de la base de datos en la tabla
*/
void Tabla::MostrarDatos()
{
    int fila=0;

    //Mostramos los datos...
    QString consulta;
    consulta.append("SELECT * FROM  plantas");

    QSqlQuery consultar(db);
    consultar.prepare(consulta);

    if(consultar.exec()) //Devuelve un booleano
        qDebug()<<"Se ha consultado correctamente";
    else
    {
        qDebug()<<"No se ha consultado correctamente";
        qDebug()<<"ERROR!"<<consultar.lastError();
    }

    ui->tableWidget_Datos->setRowCount(0);
    while(consultar.next())//hasta que el string este vacio
    {
        ui->tableWidget_Datos->insertRow(fila);//Agrego una fila

        for (int i=0; i<7; i++)
        {
             ui->tableWidget_Datos->setItem(fila , i ,
             new QTableWidgetItem(consultar.value(i).toByteArray().constData()) );
        }
        fila++;
   }
}

/**
    \fn  	on_pushButton_Borrar_clicked()
    \brief  se activa al presionar el botón de borrar y borra la fila elegida
*/
void Tabla::on_pushButton_Borrar_clicked()
{
    int fila=ui->tableWidget_Datos->selectionModel()->currentIndex().row();
    QString id = ui->tableWidget_Datos->item(fila,0)->text();
    //Obtiene el el id de la selda seleccionada

    QSqlQuery consultar(db);
    consultar.prepare("DELETE FROM plantas WHERE id = "+id+"");

   if(consultar.exec())//Devuelve un booleano
   {
       qDebug()<<"Se borro con exito" << id;
       ui->tableWidget_Datos->removeRow(ui->tableWidget_Datos->selectionModel()->currentIndex().row());
       ui->pushButton_Borrar->setEnabled(isEnabled=false);
   }
   else
   {
       qDebug()<<"No se pudo eliminar";
       qDebug()<<"ERROR!"<<consultar.lastError();
       QMessageBox::critical(NULL,"Error","No se pudo borrar el elemento seleccionado");
   }
}

/**
    \fn  	on_tableWidget_Datos_cellChanged(int row, int column)
    \brief  cuando se cambia el contenido de una celda actualiza el valor de la base
*/
void Tabla::on_tableWidget_Datos_cellChanged(int row, int column)
{
    if(dobleClick)//Si no estuviera entra también cada vez que crea celdas
    {
        QString columnas[] = {"temp_max", "temp_min", "nivel_riego", "nivel_luz", "precaucion",};
        //Nombres reales de las columnas en la base de datos
        QString campo = columnas[column-2];//Resto dos por el id y el nombre
        QString ID = ui->tableWidget_Datos->item(row,0)->text(); //Obtengo el id
        QString value = ui->tableWidget_Datos->item(row, column)->text();//Contenido de la celda
        qDebug() << campo;

        QSqlQuery qry;
        qry.prepare( "UPDATE plantas SET "+campo+" = '"+value+"' WHERE id ="+ID+"");

        if( !qry.exec() )
            qDebug() << qry.lastError();
        else
            qDebug() << "Updated " << campo << "!";
        huboCambios = true;
    }
    dobleClick = false;
}

/**
    \fn  	on_tableWidget_Datos_itemSelectionChanged()
    \brief  cuando se cambia la selección del mouse se activa/desactica
            la opcion de borrar
*/
void Tabla::on_tableWidget_Datos_itemSelectionChanged()
{
    static QModelIndex IndiceAnterior;
    //qDebug() << ui->tableWidget_Datos->currentIndex();

    if (IndiceAnterior==ui->tableWidget_Datos->currentIndex())
        ui->pushButton_Borrar->setEnabled(isEnabled=false);
    else
         ui->pushButton_Borrar->setEnabled(isEnabled=true);
    IndiceAnterior = ui->tableWidget_Datos->currentIndex();
}

/**
    \fn  	void Tabla::on_pushButton_Agregar_clicked()
    \brief  Slot del botón de agregar clickeado
*/
void Tabla::on_pushButton_Agregar_clicked()
{
    //Abro la segunda ventana
    Datos dialog;
    dialog.setModal(true);
    dialog.exec();
    MostrarDatos();
}

/**
    \fn  	void Tabla::on_tableWidget_Datos_cellDoubleClicked(int, int )
    \brief  Slot de la tabla para una celda a la que se le hace doble click
*/
void Tabla::on_tableWidget_Datos_cellDoubleClicked(int, int )
{
    dobleClick = true;
}
