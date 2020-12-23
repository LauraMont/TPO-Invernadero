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
    ui->label_HUM_AMB->setVisible(false);
    ui->label_hum_amb->setVisible(false);
    ui->label_HUM_TIERRA->setVisible(false);
    ui->label_hum_tierra->setVisible(false);
    ui->iniciar->setEnabled(false);
    ui->radioButton_Red->toggle();
    iniciado = 0;

    Inicio.setWidth(INICIO_WIDTH); //Seteo los tamaños en los Qsize
    Inicio.setHeight(INICIO_HEIGTH);

    Datos.setWidth(DATOS_WIDTH); //Seteo los tamaños en los Qsize
    Datos.setHeight(DATOS_HEIGTH);

    Warning.setWidth(WARNING_WIDTH);
    Warning.setWidth(WARNING_HEIGTH);

    this->resize(Inicio); // Seteo el tamaño inicial
    timerId = startTimer(1000);

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
    killTimer(timerId);
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
                    "temp_min    VARCHAR(100),"
                    "temp_max    VARCHAR(100),"
                    "hum_tierra  VARCHAR(100),"
                    "hum_amb     VARCHAR(100),"
                    "precaucion  VARCHAR(100),"
                    "ruta_imagen VARCHAR(200)"
                    ");");
   QSqlQuery crear(db);
   if(!crear.prepare(consulta))
       QMessageBox::critical(NULL, "Base de Datos", "No se pudo preparar la consulta de nombres");
   if (!crear.exec()) //Devuelve un booleano
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
    ui->label_TMAX->setText(consultar.value(2).toString() + " °C");
    ui->label_TMIN->setText(consultar.value(3).toString() + " °C");
    ui->label_HTIERRA->setText(consultar.value(4).toString() + " %");
    ui->label_HAMB->setText(consultar.value(5).toString() + " %");
    ui->label_PREC->setText(consultar.value(6).toString());
    imagen = consultar.value(7).toString();
    if(imagen.length()) //Si tiene una imagen asociada la cargo, sino cargo la default
    {
        QPixmap* MiPixMap = new QPixmap(imagen);
        ui->label_invernadero->setPixmap(*MiPixMap);
        ui->label_invernadero->setScaledContents(true);
    }
    else
    {
        QPixmap* MiPixMap = new QPixmap(rutaFotos + "sin nombre.png");
        ui->label_invernadero->setPixmap(*MiPixMap);
        ui->label_invernadero->setScaledContents(true);
    }
    ui->iniciar->setEnabled(true);
}

/**
    \fn  	void MainWindow::cargarDefault()
    \brief	Carga la foto por default y limpia los label si se elige la opcion por default
*/
void MainWindow::cargarDefault()
{
    QPixmap* MiPixMap = new QPixmap(rutaFotos + "invernadero.png");
    ui->iniciar->setEnabled(false);
    ui->label_invernadero->setPixmap(*MiPixMap);
    ui->label_invernadero->setScaledContents(true);
    ui->label_TMAX->clear();
    ui->label_TMIN->clear();
    ui->label_HAMB->clear();
    ui->label_HTIERRA->clear();
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
}

/**
    \fn  	void MainWindow::on_iniciar_clicked()
    \brief	Inicia el cuidado, bloqueando el combo box y las configuraciones
*/
void MainWindow::on_iniciar_clicked()
{
    if(ui->iniciar->text() == "INICIAR")
    {
        if(!puerto->isOpen())
        {
            puerto->setPortName("/dev/ttyUSB0");

            if(puerto->open(QSerialPort::ReadWrite))
            {
                enable_gui();
                enviar_datos();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Error abriendo puerto: " + puerto->errorString());
            }
        }
    }
    else
    {
        disable_gui();
        terminar();
        puerto->flush();//Envio el ultimo dato que quede en el buffer antes de cerrar el puerto
        puerto->close();
    }
}
/**
    \fn  closeEvent
    \brief Prohibe al usuario cerrar la aplicación si aun no ha detenido el proceso
*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (iniciado)
    {
        QMessageBox::critical(this,"Error", "Detenga el proceso antes de cerrar");
        event->ignore();
    }
    else
    {
        event->accept();
        qDebug() << "Hasta luego, vuelva prontos";
    }
}
/**
    \fn  enable_gui
    \brief Modifica el gui, para habilitar los elementos permitidos mientras el proceso esté activo
*/
void MainWindow::enable_gui()
{
    iniciado = 1;
    this->resize(Datos); //Agrando el tamaño para que entren los datos
    ui->radioButton_Red->setEnabled(false);
    ui->radioButton_Tanque->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->configuraciones->setEnabled(false);
    ui->iniciar->setText("DETENER");

    ui->label_TACTUAL->setVisible(true);
    ui->label_tactual->setVisible(true);
    ui->label_HUM_AMB->setVisible(true);
    ui->label_hum_amb->setVisible(true);
    ui->label_HUM_TIERRA->setVisible(true);
    ui->label_hum_tierra->setVisible(true);
}
/**
    \fn  disable_gui
    \brief Modifica el gui, para deshabilitar los elementos mientras el proceso esté inactivo
*/
void MainWindow::disable_gui()
{
    iniciado  = 0;
    this->resize(Inicio);//Achico el tamaño para sacar los datos
    ui->radioButton_Red->setEnabled(true);
    ui->radioButton_Tanque->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->configuraciones->setEnabled(true);
    ui->iniciar->setText("INICIAR");

    ui->label_TACTUAL->setVisible(false);
    ui->label_tactual->setVisible(false);
    ui->label_HUM_AMB->setVisible(false);
    ui->label_hum_amb->setVisible(false);
    ui->label_HUM_TIERRA->setVisible(false);
    ui->label_hum_tierra->setVisible(false);
}
/**
    \fn  enviar_datos
    \brief Envia los datos al puerto serie de la planta seleccionada, para la inicialización
*/
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
    data.append('1');
    valor = consultar.value(2).toUInt(); //Temperatura Maxima
    data.append(valor/10 + '0');
    valor%= 10;
    data.append(valor + '0');
    valor = consultar.value(3).toUInt();//Temperatura Minima
    data.append(valor/10 + '0');
    valor%= 10;
    data.append(valor + '0');
    valor = consultar.value(4).toUInt();//Humedad tierra
    data.append(valor/10 + '0');
    valor%= 10;
    data.append(valor + '0');
    valor = consultar.value(5).toUInt();//Humedad ambiente
    data.append(valor/10 + '0');
    valor%= 10;
    data.append(valor + '0');
    valor = ui->radioButton_Red->isChecked();
    data.append(valor + '0');
    data.append('%');
    data.append(consultar.value(1).toString());
    data.append('&');
    data.append('#');
    puerto->write(data);
}
/**
    \fn  terminar
    \brief Envia los datos al puerto serie, para enviar la trama de finalización del cuidado
*/
void MainWindow::terminar()
{
    QByteArray data;
    data.append('$');
    data.append('2');       //Comando para detener
    data.append('#');
    puerto->write(data);
}
/**
    \fn  data_in
    \brief Lee el puerto, cada vez que recibe un dato, hasta que no tenga más que leer
*/

void MainWindow::data_in()
{
    do{
        rx_SM(puerto->read(1));
    }while(puerto->bytesAvailable() != 0);
}
/**
    \fn  rx_SM
    \brief Maquina de estado para la recepción de datos enviados desde el micro
*/
void MainWindow::rx_SM(QByteArray byte_in)
{
    QByteArray data;
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
    } // End case RX_SM_WAITING_DATA

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
        } // End case RX_SM_WAITING_END

    case RX_SM_ERR:
    {
        QString Error ="ERER";
        memcpy(data_buffer,Error.toStdString().c_str(),Error.size());
        actualizar_datos();

        rx_state = RX_SM_WAITING_START;

        break;
    } // End case RX_SM_ERR


        default:
            rx_state=RX_SM_WAITING_START;
        } // End switch(rx_state)
}
/**
    \fn  check_if_data_valid
    \brief Comprueba si los datos recibidos son datos validos o no
*/
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
/**
    \fn  actualizar_datos
    \brief actualiza los datos en la aplicación cada vez que recibe una nueva medición
*/
void MainWindow::actualizar_datos()
{

    int humedad, temperatura, humedad_tierra, estado;

    estado=(data_buffer[6]-'0');

    humedad_tierra=(data_buffer[5]-'0');
    humedad_tierra+=(data_buffer[4]-'0')*10;

    humedad=(data_buffer[3]-'0');
    humedad+=(data_buffer[2]-'0')*10;

    temperatura=(data_buffer[1]-'0');
    temperatura+=(data_buffer[0]-'0')*10;

    ui->label_TACTUAL->setText( QString::number(temperatura) + " °C");
    ui->label_HUM_AMB->setText( QString::number(humedad) + " %");
    ui->label_HUM_TIERRA->setText( QString::number(humedad_tierra) + " %");

    switch(estado)
    {
        case WAITING: ui->label_ESTADOS->setText("ESPERANDO"); break;

        case CARING: ui->label_ESTADOS->setText("CUIDANDO"); break;

        case WATERING: ui->label_ESTADOS->setText("REGANDO"); break;

        case WARMING: ui->label_ESTADOS->setText("CALENTANDO"); break;

        case COOLING: ui->label_ESTADOS->setText("ENFRIANDO"); break;

        case VENTILATE: ui->label_ESTADOS->setText("VENTILANDO"); break;

        case ALARM: ui->label_ESTADOS->setText("TANQUE VACIO"); break;
    }
}
/**
    \fn  timerEvent
    \brief Actua cada vez que vence el timer, y comprueba si el estado sigue conectado o se desconectó el puerto
*/
void MainWindow::timerEvent(QTimerEvent *event)
{
    static bool desconexion = false;
    if(iniciado)
    {
        if(QFile::exists("/dev/ttyUSB0"))
        {
            if(desconexion)
            {
                if(!puerto->isOpen())
                {
                    puerto->setPortName("/dev/ttyUSB0");

                    if(puerto->open(QSerialPort::ReadWrite))
                    {
                        this->resize(Datos);
                        ui->label_datos->setText("                   Datos en tiempo real");
                    }
                }
                desconexion = false;
            }
        }
        else
        {
            desconexion = true;
            puerto->close();
            this->resize(381, 500);
            ui->label_datos->setText("Pérdida de conexión, reconectando...");
         }

     }
}
