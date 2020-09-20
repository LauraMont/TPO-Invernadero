#ifndef DATOS_H
#define DATOS_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>//Contiene los recursos  para el manejo de bases de datos
#include <QSqlQuery>//Consultas y requerimientos a la base de datos
#include <QSqlError>//Nos permite conocer los tipos de errores en las bases de datos
#include <QFileDialog>
#include "mainwindow.h"

namespace Ui {
class Datos;
}

class Datos : public QDialog
{
    Q_OBJECT

public:
    explicit Datos(QWidget *parent = nullptr);
    ~Datos();
    void insertarPlanta();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Datos *ui;
};

#endif // DATOS_H
