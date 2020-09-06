#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>//Contiene los recursos  para el manejo de bases de datos
#include <QSqlQuery>//Consultas y requerimientos a la base de datos
#include <QSqlError>//Nos permite conocer los tipos de errores en las bases de datos
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void CrearTablaUsuarios ();

    void insertarUsuario();

    void mostrarDatos();

private slots:
    void on_pushButton_Agregar_clicked();

    void on_pushButton_Borrar_clicked();

    void on_tableWidget_Datos_cellClicked(int, int);

    void on_tableWidget_Datos_cellChanged(int row, int column);

    void on_tableWidget_Datos_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool isEnabled= false;
    bool guardar = false;
    int fila;
    int columna;
};
#endif // MAINWINDOW_H
