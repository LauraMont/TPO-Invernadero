#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include "unistd.h"

QSqlDatabase db; //Variable global para que la pueda tomar la otra aplicación como extern
QString rutaFotos = RUTA_FOTOS;
QString elijaPlanta = "--Elija una planta--";

/**
    \fn  	MainWindow(QWidget *parent)
    \brief	Constructor
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    puerto = new QSerialPort(this);

    puerto->setBaudRate(QSerialPort::Baud9600);
    puerto->setStopBits(QSerialPort::OneStop);
    puerto->setParity(QSerialPort::NoParity);
    puerto->setFlowControl(QSerialPort::NoFlowControl);
    puerto->setDataBits(QSerialPort::Data8);

    rx_state= RX_SM_WAITING_START;

    ui->label_TACTUAL->setVisible(false);
    ui->label_tactual->setVisible(false);
    ui->label_HUMEDAD->setVisible(false);
    ui->label_humedad->setVisible(false);

    qDebug()<<"Aplicacion iniciada..."; // Creacion de la base de datos...
    crearTablaPlantas();
    QPixmap* MiPixMap = new QPixmap(rutaFotos + "invernadero.png");
    ui->label_invernadero->resize(128,128);
    ui->label_invernadero->setPixmap(*MiPixMap);
    ui->label_invernadero->setScaledContents(true);
    cargarPlantas();
    connect(puerto, &QSerialPort::readyRead, this, &MainWindow::data_in);
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
                    "temp_min VARCHAR(100),"
                    "temp_max VARCHAR(100),"
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
    QSqlQuery consultar(db), cantidad(db);
    QString planta;
    int cant;
    ui->comboBox->addItem(elijaPlanta);
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
    ui->label_TMIN->setText(consultar.value(2).toString() + " °C");
    ui->label_TMAX->setText(consultar.value(3).toString() + " °C");
    ui->label_NRIEGO->setText(consultar.value(4).toString() + " %");
    ui->label_NLUZ->setText(consultar.value(5).toString() + " %");
    ui->label_PREC->setText(consultar.value(6).toString());
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
    eleccion = arg1;//Guardo la eleccion del usuario
    if(arg1 == elijaPlanta)
        cargarDefault();
    else
        cargarDatos();
}

/**
    \fn  	void MainWindow::on_configuraciones_clicked()
    \brief	Abre la ventana para editar/agregar plantas
*/
void MainWindow::on_configuraciones_clicked()
{
    //Abro la segunda ventana
    Tabla tabla;
    tabla.setModal(true);
    tabla.exec();
    ui->comboBox->clear();
    cargarPlantas();//Vuelve a cargar las plantas en el combo box por si se agrego una
    if(ui->comboBox->findText(eleccion) < 0)//Si se borró la eleccion cargo la default
        eleccion = elijaPlanta;
    ui->comboBox->setCurrentText(eleccion);
    emit on_comboBox_activated(eleccion);//Envio la señal para que cargue los datos
    qDebug() << "Te mando el elemento: " << ui->comboBox->currentIndex();
}

/**
    \fn  	void MainWindow::on_iniciar_clicked()
    \brief	Inicia el cuidado, bloqueando el combo box y las configuraciones
*/
void MainWindow::on_iniciar_clicked()
{
    if(ui->iniciar->text() == "INICIAR")
    {
        if(!puerto->isOpen()) {
            puerto->setPortName("/dev/ttyUSB0");

            if(puerto->open(QSerialPort::ReadWrite)) {

                enable_gui();
                enviar_datos();
            }
            else {
                QMessageBox::critical(this,
                                      "Error",
                                      "Error abriendo puerto: " + puerto->errorString());
            }
        }
    }
    else {
        disable_gui();
        terminar();
//        puerto->close();   PREGUNTAR AUGUSTO Cómo cerrar el puerto y que envie el dato anterior.
    }
}

void MainWindow::enable_gui()
{
    ui->comboBox->setEnabled(false);
    ui->configuraciones->setEnabled(false);
    ui->iniciar->setText("DETENER");

    ui->label_TACTUAL->setVisible(true);
    ui->label_tactual->setVisible(true);
    ui->label_HUMEDAD->setVisible(true);
    ui->label_humedad->setVisible(true);
}

void MainWindow::disable_gui()
{
    ui->comboBox->setEnabled(true);
    ui->configuraciones->setEnabled(true);
    ui->iniciar->setText("INICIAR");

    ui->label_TACTUAL->setVisible(false);
    ui->label_tactual->setVisible(false);
    ui->label_HUMEDAD->setVisible(false);
    ui->label_humedad->setVisible(false);
}

void MainWindow::enviar_datos()
{
    QSqlQuery consultar(db);
    consultar.prepare("SELECT * FROM plantas WHERE planta = '"+ui->comboBox->currentText()+"' ");


    if(!consultar.exec()) //Devuelve un booleano
        qDebug()<<"ERROR EN LA CONSULTA!"<<consultar.lastError();

    consultar.next();

    unsigned int valor;

    QByteArray data;
    data.append('$');
    valor = consultar.value(2).toUInt();
    qDebug() << "Valor: " << valor;
    data.append(valor/10 + '0');
    valor%= 10;
    data.append(valor + '0');
    data.append('%');
    valor = consultar.value(3).toUInt();
    data.append(valor/10 + '0');
    valor%= 10;
    data.append(valor + '0');
    data.append('%');
    valor = consultar.value(4).toUInt();
    data.append(valor + '0');
    data.append('&');
    puerto->write(data);
}

void MainWindow::terminar()
{
    QByteArray data;
    data.append('#');
    puerto->write(data);
}

void MainWindow::data_in()
{
    do
        {
            rx_SM(puerto->read(1));
    }while(puerto->bytesAvailable() != 0);
}

void MainWindow::rx_SM(QByteArray byte_in)
{
    switch(rx_state)
        {
        case RX_SM_WAITING_START:
        {
            if(!byte_in.compare("$"))
            {
                rx_state = RX_SM_WAITING_DATA;
            }

            break;
        } // End case RX_SM_WAITING_START

    case RX_SM_WAITING_DATA:
    {
        int check_data_result;

        check_data_result = check_if_data_valid(byte_in.at(0));

        if(check_data_result == 1) {
            rx_state = RX_SM_WAITING_END;
        }

        if(check_data_result == -1) {
            ;
            rx_state = RX_SM_ERR;
        }


        break;
    } // End case RX_SM_WAITING_START

        case RX_SM_WAITING_END:
        {
            if(!byte_in.compare("#"))
            {
                actualizar_datos();
                rx_state = RX_SM_WAITING_START;
            }
            else
            {
                rx_state = RX_SM_ERR;
            }

            break;
        } // End case RX_SM_WAITING_0D

    case RX_SM_ERR:
    {
        QString Error ="ERER";
        memcpy(data_buffer,Error.toStdString().c_str(),Error.size());
        actualizar_datos();

        rx_state = RX_SM_WAITING_START;

        break;
    } // End case RX_SM_WAITING_0D


        default:
            rx_state=RX_SM_WAITING_START;
        } // End switch(rx_state)
}

int MainWindow::check_if_data_valid(int dato_rx) {

    static int data_counter=0;

    if(dato_rx == -1) {
        return 0;
    }

    if(dato_rx < '0' || dato_rx > '9') {
        return -1;
    }

    //restart_rx_timeout();

    data_buffer[data_counter] = (char) dato_rx;
    data_counter++;

    if(data_counter >= DATA_BUFFER_SIZE) {
        data_counter = 0;
        return 1;
    }

    return 0;
}

void MainWindow::actualizar_datos()
{
    //Trama $TEHU#      TE: dos digitos de temp, HU:dos digitos de humedad

    int humedad, temperatura;

    humedad=(data_buffer[3]-'0');
    humedad+=(data_buffer[2]-'0')*10;

    temperatura=(data_buffer[1]-'0');
    temperatura+=(data_buffer[0]-'0')*10;

    qDebug() << "Recibí: " << temperatura << " °C" ;
    qDebug() << "Recibí: " << humedad << " %";
    ui->label_TACTUAL->setText( QString::number(temperatura) + " °C");
    ui->label_HUMEDAD->setText( QString::number(humedad) + " %");
}
