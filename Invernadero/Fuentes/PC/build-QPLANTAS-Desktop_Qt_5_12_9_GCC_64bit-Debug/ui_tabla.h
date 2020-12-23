/********************************************************************************
** Form generated from reading UI file 'tabla.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLA_H
#define UI_TABLA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tabla
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget_Datos;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Borrar;
    QPushButton *pushButton_Agregar;

    void setupUi(QDialog *Tabla)
    {
        if (Tabla->objectName().isEmpty())
            Tabla->setObjectName(QString::fromUtf8("Tabla"));
        Tabla->resize(882, 451);
        layoutWidget = new QWidget(Tabla);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 881, 451));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget_Datos = new QTableWidget(layoutWidget);
        if (tableWidget_Datos->columnCount() < 7)
            tableWidget_Datos->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_Datos->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget_Datos->setObjectName(QString::fromUtf8("tableWidget_Datos"));
        tableWidget_Datos->setAutoFillBackground(false);
        tableWidget_Datos->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget_Datos->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_Datos->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget_Datos, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_Borrar = new QPushButton(layoutWidget);
        pushButton_Borrar->setObjectName(QString::fromUtf8("pushButton_Borrar"));
        pushButton_Borrar->setEnabled(false);

        horizontalLayout->addWidget(pushButton_Borrar);

        pushButton_Agregar = new QPushButton(layoutWidget);
        pushButton_Agregar->setObjectName(QString::fromUtf8("pushButton_Agregar"));

        horizontalLayout->addWidget(pushButton_Agregar);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Tabla);

        QMetaObject::connectSlotsByName(Tabla);
    } // setupUi

    void retranslateUi(QDialog *Tabla)
    {
        Tabla->setWindowTitle(QApplication::translate("Tabla", "Base de Datos", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_Datos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Tabla", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_Datos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Tabla", "Planta", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_Datos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Tabla", "Temp Min", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_Datos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Tabla", "Temp Max", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_Datos->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Tabla", "Hum Tierra", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_Datos->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Tabla", "Hum Amb", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_Datos->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Tabla", "Precauci\303\263n", nullptr));
        pushButton_Borrar->setText(QApplication::translate("Tabla", "Borrar", nullptr));
        pushButton_Agregar->setText(QApplication::translate("Tabla", "Agregar Planta", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tabla: public Ui_Tabla {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLA_H
