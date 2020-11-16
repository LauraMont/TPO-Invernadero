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

#define RUTA_FOTOS "../DB-PLANTAS-V3/Recursos/"

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

    void enviar_datos();

    void terminar();

private:
    Ui::MainWindow *ui;
    QString eleccion;
    QSerialPort* puerto;
};
#endif // MAINWINDOW_H
