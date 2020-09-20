#include "mainwindow.h"
#include "ui_mainwindow.h"

QSqlDatabase db; //Variable global para que la pueda tomar la otra aplicación como extern
QString rutaFotos = RUTA_FOTOS;
bool huboCambios = false;//Sirve para indicar si hubo cambios en los
                         //datos de la planta que esta cargada

/**
    \fn  	MainWindow(QWidget *parent)
    \brief	Constructor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug()<<"Aplicacion iniciada..."; // Creacion de la base de datos...
    crearTablaPlantas();
    QPixmap* MiPixMap = new QPixmap(rutaFotos + "invernadero.png");
    ui->label_invernadero->resize(128,128);
    ui->label_invernadero->setPixmap(*MiPixMap);
    ui->label_invernadero->setScaledContents(true);
    ui->comboBox->addItem("--Elija una planta--");
    cargarPlantas();
}

/**
    \fn  	MainWindow::~MainWindow()
    \brief	Desctructor
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
    \fn  	void MainWindow::crearTablaPlantas()
    \brief	Se encarga de crear la base de datos o conectarse si ya esta creada
*/
void MainWindow::crearTablaPlantas()
{
    //Creacion de tabla...
    QString  nombre = "../Base de Datos/BDPLANTAS.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombre);
    if(db.open())
        qDebug()<<"Se ha conectado a la base de datos.";
    else
        qDebug()<<"ERROR! No se ha conectado a la base de datos.";

    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS   plantas  (   "
                    "id INTEGER PRIMARY KEY AUTOINCREMENT ,"
                    "planta VARCHAR(100),"
                    "temp_max VARCHAR(100),"
                    "temp_min VARCHAR(100),"
                    "nivel_riego VARCHAR(100),"
                    "nivel_luz VARCHAR(100),"
                    "precaucion VARCHAR(100),"
                    "ruta_imagen VARCHAR(200)"
                    ");");
   QSqlQuery crear(db);
   if(!crear.prepare(consulta))
       QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta de nombres");
   if (crear.exec()) //Devuelte un booleano
       qDebug()<<"La tabla usuarios existe o se ha creado correctamente";
   else
       qDebug()<<"ERROR!"<<crear.lastError();
}

/**
    \fn  	void MainWindow::cargarPlantas()
    \brief	Lee la BD y carga los nombres de las plantas en el combo box
*/
void MainWindow::cargarPlantas()
{
    QSqlQuery consultar(db);
    QString planta;

    /*consultar.prepare("SELECT COUNT(*) FROM plantas");            NO FUNCIONA :(
    consultar.first();
    int count = consultar.value(0).toInt();
    qDebug() << count;*/
    consultar.prepare("SELECT planta FROM plantas");

    if(!consultar.exec()) //Devuelve un booleano
        qDebug()<<"ERROR EN LA CONSULTA!"<<consultar.lastError();
    ui->comboBox->clear();
    ui->comboBox->addItem("--Elija una planta--");
    cargarDefault();
    while(consultar.next())//hasta que el string este vacio
    {
        for (int i=0; i<5; i++)
        {
            planta = consultar.value(i).toString();//Elemento leido de la BD
            if(planta.length() && !yaExiste(planta))
                ui->comboBox->addItem(planta);
        }
      /*La consulta devuelve valores en blanco, por eso chequeo la longitud y
        verifico que el valor no exista ya en la lista, sino  vuelve a cargar
        nombres que ya estan cuando se abre y cierra las configuraciones*/
    }

}

/**
    \fn  	void MainWindow::cargarDatos()
    \brief	Carga los datos de la planta elegida en los labels
*/
void MainWindow::cargarDatos()
{
    QString texto = ui->comboBox->currentText();
    QString imagen;
    QSqlQuery consultar(db);
    consultar.prepare("SELECT * FROM plantas WHERE planta = '"+texto+"' ");

    if(!consultar.exec()) //Devuelve un booleano
        qDebug()<<"ERROR EN LA CONSULTA!"<<consultar.lastError();

    consultar.next();
    //Como tomo toda la fila también estan el id y el nombre de la planta,
    //por eso arranca desde el 2
    ui->label_TMAX->setText(consultar.value(2).toString());
    ui->label_TMIN->setText(consultar.value(3).toString());
    ui->label_NRIEGO->setText(consultar.value(4).toString());
    ui->label_NLUZ->setText(consultar.value(5).toString());
    ui->label_PREC->setText(consultar.value(6).toString());
//    qDebug() << consultar.value(7).toString();
    imagen = consultar.value(7).toString();
    if(imagen.length()) //Si tiene una imagen asociada la cargo, sino cargo la default
    {
        QPixmap* MiPixMap = new QPixmap(consultar.value(7).toString());
        ui->label_invernadero->setPixmap(*MiPixMap);
        ui->label_invernadero->setScaledContents(true);
    }
    else
    {
        QPixmap* MiPixMap = new QPixmap(rutaFotos + "sin nombre.png");
        ui->label_invernadero->setPixmap(*MiPixMap);
        ui->label_invernadero->setScaledContents(true);
    }

}

/**
    \fn  	void MainWindow::cargarDefault()
    \brief	Carga la foto por default y limpia los label si se elige la opcion por default
*/
void MainWindow::cargarDefault()
{
    QPixmap* MiPixMap = new QPixmap(rutaFotos + "invernadero.png");
    ui->label_invernadero->setPixmap(*MiPixMap);
    ui->label_invernadero->setScaledContents(true);
    ui->label_TMAX->clear();
    ui->label_TMIN->clear();
    ui->label_NRIEGO->clear();
    ui->label_NLUZ->clear();
    ui->label_PREC->clear();
}

/**
    \fn  	bool MainWindow::yaExiste(QString &planta)
    \brief	Devuelve true si el string ya esta en la lista del combobox
*/
bool MainWindow::yaExiste(QString &planta)
{
    bool salida = false;
    int cant = ui->comboBox->count();
    for(int i=0;i<cant;i++)
    {
        if(ui->comboBox->itemText(i) == planta)//Por cada item evaluo si es igual a planta
        {
            salida = true;
            break;
        }
    }
    return salida;
}

/**
    \fn  	void MainWindow::on_comboBox_activated(const QString &arg1)
    \brief	Slot de activación del combo box
*/
void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "--Elija una planta--")
        cargarDefault();
    else
        cargarDatos();
}

/**
    \fn  	void MainWindow::on_pushButton_clicked()
    \brief	Slot de botón de configuración
*/
void MainWindow::on_pushButton_clicked()
{
    //Abro la segunda ventana
    Tabla tabla;
    tabla.setModal(true);
    tabla.exec();
    cargarPlantas();//Vuelve a cargar las plantas en el combo box por si se agrego una
    if(huboCambios) cargarDatos(); //Para que recargue datos solo si se cambio alguno
}
