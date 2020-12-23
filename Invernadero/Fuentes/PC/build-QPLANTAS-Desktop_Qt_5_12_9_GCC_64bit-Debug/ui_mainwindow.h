/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *comboBox;
    QPushButton *configuraciones;
    QLabel *label_invernadero;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_tmax;
    QLabel *label_tmin;
    QLabel *label_prec;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_TMIN;
    QLabel *label_TMAX;
    QLabel *label_PREC;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_h_tierra;
    QLabel *label_h_amb;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_HTIERRA;
    QLabel *label_HAMB;
    QPushButton *iniciar;
    QRadioButton *radioButton_Red;
    QRadioButton *radioButton_Tanque;
    QLabel *label_suministro;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_tactual;
    QLabel *label_hum_amb;
    QLabel *label_hum_tierra;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_TACTUAL;
    QLabel *label_HUM_AMB;
    QLabel *label_HUM_TIERRA;
    QLabel *label_datos;
    QFrame *line;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_estado;
    QLabel *label_ESTADOS;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(381, 624);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 150, 181, 41));
        configuraciones = new QPushButton(centralwidget);
        configuraciones->setObjectName(QString::fromUtf8("configuraciones"));
        configuraciones->setGeometry(QRect(320, 20, 41, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Recursos/configuraciones.png"), QSize(), QIcon::Normal, QIcon::Off);
        configuraciones->setIcon(icon);
        configuraciones->setIconSize(QSize(32, 32));
        label_invernadero = new QLabel(centralwidget);
        label_invernadero->setObjectName(QString::fromUtf8("label_invernadero"));
        label_invernadero->setGeometry(QRect(130, 20, 131, 91));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 210, 107, 85));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_tmax = new QLabel(layoutWidget);
        label_tmax->setObjectName(QString::fromUtf8("label_tmax"));

        verticalLayout->addWidget(label_tmax);

        label_tmin = new QLabel(layoutWidget);
        label_tmin->setObjectName(QString::fromUtf8("label_tmin"));

        verticalLayout->addWidget(label_tmin);

        label_prec = new QLabel(layoutWidget);
        label_prec->setObjectName(QString::fromUtf8("label_prec"));

        verticalLayout->addWidget(label_prec);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 210, 71, 79));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_TMIN = new QLabel(layoutWidget1);
        label_TMIN->setObjectName(QString::fromUtf8("label_TMIN"));

        verticalLayout_2->addWidget(label_TMIN);

        label_TMAX = new QLabel(layoutWidget1);
        label_TMAX->setObjectName(QString::fromUtf8("label_TMAX"));

        verticalLayout_2->addWidget(label_TMAX);

        label_PREC = new QLabel(layoutWidget1);
        label_PREC->setObjectName(QString::fromUtf8("label_PREC"));

        verticalLayout_2->addWidget(label_PREC);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(200, 210, 120, 55));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_h_tierra = new QLabel(layoutWidget2);
        label_h_tierra->setObjectName(QString::fromUtf8("label_h_tierra"));

        verticalLayout_3->addWidget(label_h_tierra);

        label_h_amb = new QLabel(layoutWidget2);
        label_h_amb->setObjectName(QString::fromUtf8("label_h_amb"));

        verticalLayout_3->addWidget(label_h_amb);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(320, 210, 51, 51));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_HTIERRA = new QLabel(layoutWidget3);
        label_HTIERRA->setObjectName(QString::fromUtf8("label_HTIERRA"));

        verticalLayout_4->addWidget(label_HTIERRA);

        label_HAMB = new QLabel(layoutWidget3);
        label_HAMB->setObjectName(QString::fromUtf8("label_HAMB"));

        verticalLayout_4->addWidget(label_HAMB);

        iniciar = new QPushButton(centralwidget);
        iniciar->setObjectName(QString::fromUtf8("iniciar"));
        iniciar->setGeometry(QRect(130, 380, 101, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        iniciar->setFont(font);
        radioButton_Red = new QRadioButton(centralwidget);
        radioButton_Red->setObjectName(QString::fromUtf8("radioButton_Red"));
        radioButton_Red->setGeometry(QRect(40, 340, 133, 27));
        radioButton_Tanque = new QRadioButton(centralwidget);
        radioButton_Tanque->setObjectName(QString::fromUtf8("radioButton_Tanque"));
        radioButton_Tanque->setGeometry(QRect(230, 340, 133, 27));
        label_suministro = new QLabel(centralwidget);
        label_suministro->setObjectName(QString::fromUtf8("label_suministro"));
        label_suministro->setGeometry(QRect(20, 310, 95, 21));
        layoutWidget4 = new QWidget(centralwidget);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 480, 108, 81));
        verticalLayout_5 = new QVBoxLayout(layoutWidget4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_tactual = new QLabel(layoutWidget4);
        label_tactual->setObjectName(QString::fromUtf8("label_tactual"));

        verticalLayout_5->addWidget(label_tactual);

        label_hum_amb = new QLabel(layoutWidget4);
        label_hum_amb->setObjectName(QString::fromUtf8("label_hum_amb"));

        verticalLayout_5->addWidget(label_hum_amb);

        label_hum_tierra = new QLabel(layoutWidget4);
        label_hum_tierra->setObjectName(QString::fromUtf8("label_hum_tierra"));

        verticalLayout_5->addWidget(label_hum_tierra);

        layoutWidget5 = new QWidget(centralwidget);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(130, 480, 91, 81));
        verticalLayout_6 = new QVBoxLayout(layoutWidget5);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_TACTUAL = new QLabel(layoutWidget5);
        label_TACTUAL->setObjectName(QString::fromUtf8("label_TACTUAL"));

        verticalLayout_6->addWidget(label_TACTUAL);

        label_HUM_AMB = new QLabel(layoutWidget5);
        label_HUM_AMB->setObjectName(QString::fromUtf8("label_HUM_AMB"));

        verticalLayout_6->addWidget(label_HUM_AMB);

        label_HUM_TIERRA = new QLabel(layoutWidget5);
        label_HUM_TIERRA->setObjectName(QString::fromUtf8("label_HUM_TIERRA"));

        verticalLayout_6->addWidget(label_HUM_TIERRA);

        label_datos = new QLabel(centralwidget);
        label_datos->setObjectName(QString::fromUtf8("label_datos"));
        label_datos->setGeometry(QRect(10, 440, 361, 21));
        QFont font1;
        font1.setPointSize(12);
        label_datos->setFont(font1);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 420, 361, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layoutWidget6 = new QWidget(centralwidget);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(240, 480, 131, 81));
        verticalLayout_7 = new QVBoxLayout(layoutWidget6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_estado = new QLabel(layoutWidget6);
        label_estado->setObjectName(QString::fromUtf8("label_estado"));

        verticalLayout_7->addWidget(label_estado);

        label_ESTADOS = new QLabel(layoutWidget6);
        label_ESTADOS->setObjectName(QString::fromUtf8("label_ESTADOS"));

        verticalLayout_7->addWidget(label_ESTADOS);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 381, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(comboBox, configuraciones);
        QWidget::setTabOrder(configuraciones, iniciar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Invernadero", nullptr));
        configuraciones->setText(QString());
        label_invernadero->setText(QString());
        label_tmax->setText(QApplication::translate("MainWindow", "Temp Max:", nullptr));
        label_tmin->setText(QApplication::translate("MainWindow", "Temp Min:", nullptr));
        label_prec->setText(QApplication::translate("MainWindow", "Precauci\303\263n:", nullptr));
        label_TMIN->setText(QString());
        label_TMAX->setText(QString());
        label_PREC->setText(QString());
        label_h_tierra->setText(QApplication::translate("MainWindow", "Hum Tierra:", nullptr));
        label_h_amb->setText(QApplication::translate("MainWindow", "Hum Amb:", nullptr));
        label_HTIERRA->setText(QString());
        label_HAMB->setText(QString());
        iniciar->setText(QApplication::translate("MainWindow", "INICIAR", nullptr));
        radioButton_Red->setText(QApplication::translate("MainWindow", "Red", nullptr));
        radioButton_Tanque->setText(QApplication::translate("MainWindow", "Tanque", nullptr));
        label_suministro->setText(QApplication::translate("MainWindow", "Suministro:", nullptr));
        label_tactual->setText(QApplication::translate("MainWindow", "Temp:", nullptr));
        label_hum_amb->setText(QApplication::translate("MainWindow", "Hum Amb:", nullptr));
        label_hum_tierra->setText(QApplication::translate("MainWindow", "Hum Tierra:", nullptr));
        label_TACTUAL->setText(QString());
        label_HUM_AMB->setText(QString());
        label_HUM_TIERRA->setText(QString());
        label_datos->setText(QApplication::translate("MainWindow", "                   Datos en tiempo real", nullptr));
        label_estado->setText(QApplication::translate("MainWindow", "Estado:", nullptr));
        label_ESTADOS->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
