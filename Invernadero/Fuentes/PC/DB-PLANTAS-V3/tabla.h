#ifndef TABLA_H
#define TABLA_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>//Contiene los recursos  para el manejo de bases de datos
#include <QSqlQuery>//Consultas y requerimientos a la base de datos
#include <QSqlError>//Nos permite conocer los tipos de errores en las bases de datos
#include "datos.h"

namespace Ui {
class Tabla;
}

class Tabla : public QDialog
{
    Q_OBJECT

public:
    explicit Tabla(QWidget *parent = nullptr);
    ~Tabla();
    void MostrarDatos();

private slots:
    void on_pushButton_Borrar_clicked();

    void on_tableWidget_Datos_cellChanged(int row, int column);

    void on_tableWidget_Datos_itemSelectionChanged();

    void on_pushButton_Agregar_clicked();

    void on_tableWidget_Datos_cellDoubleClicked(int row, int column);

private:
    Ui::Tabla *ui;
    bool isEnabled= false;
    bool guardar = false;
    bool dobleClick = false;
};

#endif // TABLA_H
