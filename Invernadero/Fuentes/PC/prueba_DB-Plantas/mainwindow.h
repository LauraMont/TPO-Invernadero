#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>//Contiene los recursos  para el manejo de bases de datos
#include <QSqlQuery>//Consultas y requerimientos a la base de datos
#include <QSqlError>//Nos permite conocer los tipos de errores en las bases de datos
#include <QtSerialPort/QSerialPort> // Para conectar el puerto
#include "tabla.h"

#define RUTA_FOTOS "../prueba_DB-Plantas/Recursos/"
#define DATA_BUFFER_SIZE 4

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void crearTablaPlantas();
    void cargarPlantas();
    void cargarDatos();
    void cargarDefault();
    bool yaExiste(QString &);

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_configuraciones_clicked();

    void on_iniciar_clicked();

    void enable_gui();

    void disable_gui();

    void enviar_datos();

    void terminar();

    void data_in();

    int check_if_data_valid(int);

    void actualizar_datos();
private:

    void rx_SM(QByteArray byte_in);

    typedef enum
    {
        RX_SM_WAITING_START = 0,
        RX_SM_WAITING_DATA,
        RX_SM_WAITING_END,
        RX_SM_ERR,
    }rx_sm_state_en;


private:
    Ui::MainWindow *ui;
    QString eleccion;
    QSerialPort* puerto;

    QByteArray data;
    bool comm_started;

    rx_sm_state_en rx_state;
    char data_buffer[DATA_BUFFER_SIZE];

};
#endif // MAINWINDOW_H
