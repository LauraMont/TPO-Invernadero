/********************************************************************************
** Form generated from reading UI file 'datos.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATOS_H
#define UI_DATOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Datos
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_planta;
    QLabel *label_t_max;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_planta;
    QLineEdit *lineEdit_t_min;
    QLineEdit *lineEdit_t_max;
    QLineEdit *lineEdit_nivel_riego;
    QLineEdit *lineEdit_nivel_luz;
    QLineEdit *lineEdit_precaucion;
    QLineEdit *lineEdit_foto;

    void setupUi(QDialog *Datos)
    {
        if (Datos->objectName().isEmpty())
            Datos->setObjectName(QString::fromUtf8("Datos"));
        Datos->resize(515, 397);
        label = new QLabel(Datos);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 10, 101, 20));
        layoutWidget = new QWidget(Datos);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(170, 340, 180, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        layoutWidget1 = new QWidget(Datos);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 41, 154, 271));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_planta = new QLabel(layoutWidget1);
        label_planta->setObjectName(QString::fromUtf8("label_planta"));

        verticalLayout->addWidget(label_planta);

        label_t_max = new QLabel(layoutWidget1);
        label_t_max->setObjectName(QString::fromUtf8("label_t_max"));

        verticalLayout->addWidget(label_t_max);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout->addWidget(label_6);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        layoutWidget2 = new QWidget(Datos);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(223, 40, 221, 281));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_planta = new QLineEdit(layoutWidget2);
        lineEdit_planta->setObjectName(QString::fromUtf8("lineEdit_planta"));

        verticalLayout_2->addWidget(lineEdit_planta);

        lineEdit_t_min = new QLineEdit(layoutWidget2);
        lineEdit_t_min->setObjectName(QString::fromUtf8("lineEdit_t_min"));
        lineEdit_t_min->setMaxLength(2);

        verticalLayout_2->addWidget(lineEdit_t_min);

        lineEdit_t_max = new QLineEdit(layoutWidget2);
        lineEdit_t_max->setObjectName(QString::fromUtf8("lineEdit_t_max"));
        lineEdit_t_max->setMaxLength(5);

        verticalLayout_2->addWidget(lineEdit_t_max);

        lineEdit_nivel_riego = new QLineEdit(layoutWidget2);
        lineEdit_nivel_riego->setObjectName(QString::fromUtf8("lineEdit_nivel_riego"));
        lineEdit_nivel_riego->setMaxLength(1);

        verticalLayout_2->addWidget(lineEdit_nivel_riego);

        lineEdit_nivel_luz = new QLineEdit(layoutWidget2);
        lineEdit_nivel_luz->setObjectName(QString::fromUtf8("lineEdit_nivel_luz"));

        verticalLayout_2->addWidget(lineEdit_nivel_luz);

        lineEdit_precaucion = new QLineEdit(layoutWidget2);
        lineEdit_precaucion->setObjectName(QString::fromUtf8("lineEdit_precaucion"));

        verticalLayout_2->addWidget(lineEdit_precaucion);

        lineEdit_foto = new QLineEdit(layoutWidget2);
        lineEdit_foto->setObjectName(QString::fromUtf8("lineEdit_foto"));

        verticalLayout_2->addWidget(lineEdit_foto);


        retranslateUi(Datos);

        QMetaObject::connectSlotsByName(Datos);
    } // setupUi

    void retranslateUi(QDialog *Datos)
    {
        Datos->setWindowTitle(QApplication::translate("Datos", "Dialog", nullptr));
        label->setText(QApplication::translate("Datos", "Nueva Planta", nullptr));
        pushButton->setText(QApplication::translate("Datos", "Aceptar", nullptr));
        pushButton_2->setText(QApplication::translate("Datos", "Cancelar", nullptr));
        label_planta->setText(QApplication::translate("Datos", "Planta :", nullptr));
        label_t_max->setText(QApplication::translate("Datos", "Temperatura minima :", nullptr));
        label_3->setText(QApplication::translate("Datos", "Temperatura maxima :", nullptr));
        label_4->setText(QApplication::translate("Datos", "Nivel de Riego :", nullptr));
        label_5->setText(QApplication::translate("Datos", "Nivel de luz :", nullptr));
        label_6->setText(QApplication::translate("Datos", "Precacucion :", nullptr));
        pushButton_3->setText(QApplication::translate("Datos", "Cargar Foto", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Datos: public Ui_Datos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATOS_H
