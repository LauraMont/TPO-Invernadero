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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QLabel *label_TMAX;
    QLabel *label_TMIN;
    QLabel *label_PREC;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_nriego;
    QLabel *label_nluz;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_NRIEGO;
    QLabel *label_NLUZ;
    QPushButton *iniciar;
    QLabel *label_TACTUAL;
    QLabel *label_tactual;
    QLabel *label_humedad;
    QLabel *label_HUMEDAD;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(384, 490);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 160, 161, 41));
        configuraciones = new QPushButton(centralwidget);
        configuraciones->setObjectName(QString::fromUtf8("configuraciones"));
        configuraciones->setGeometry(QRect(320, 20, 41, 41));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Recursos/configuraciones.png"), QSize(), QIcon::Normal, QIcon::Off);
        configuraciones->setIcon(icon);
        configuraciones->setIconSize(QSize(32, 32));
        label_invernadero = new QLabel(centralwidget);
        label_invernadero->setObjectName(QString::fromUtf8("label_invernadero"));
        label_invernadero->setGeometry(QRect(120, 30, 131, 91));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 230, 81, 65));
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
        layoutWidget1->setGeometry(QRect(100, 230, 71, 65));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_TMAX = new QLabel(layoutWidget1);
        label_TMAX->setObjectName(QString::fromUtf8("label_TMAX"));

        verticalLayout_2->addWidget(label_TMAX);

        label_TMIN = new QLabel(layoutWidget1);
        label_TMIN->setObjectName(QString::fromUtf8("label_TMIN"));

        verticalLayout_2->addWidget(label_TMIN);

        label_PREC = new QLabel(layoutWidget1);
        label_PREC->setObjectName(QString::fromUtf8("label_PREC"));

        verticalLayout_2->addWidget(label_PREC);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(180, 230, 100, 42));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_nriego = new QLabel(layoutWidget2);
        label_nriego->setObjectName(QString::fromUtf8("label_nriego"));

        verticalLayout_3->addWidget(label_nriego);

        label_nluz = new QLabel(layoutWidget2);
        label_nluz->setObjectName(QString::fromUtf8("label_nluz"));

        verticalLayout_3->addWidget(label_nluz);

        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(290, 230, 51, 42));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_NRIEGO = new QLabel(layoutWidget3);
        label_NRIEGO->setObjectName(QString::fromUtf8("label_NRIEGO"));

        verticalLayout_4->addWidget(label_NRIEGO);

        label_NLUZ = new QLabel(layoutWidget3);
        label_NLUZ->setObjectName(QString::fromUtf8("label_NLUZ"));

        verticalLayout_4->addWidget(label_NLUZ);

        iniciar = new QPushButton(centralwidget);
        iniciar->setObjectName(QString::fromUtf8("iniciar"));
        iniciar->setGeometry(QRect(140, 310, 101, 31));
        label_TACTUAL = new QLabel(centralwidget);
        label_TACTUAL->setObjectName(QString::fromUtf8("label_TACTUAL"));
        label_TACTUAL->setGeometry(QRect(70, 360, 69, 17));
        label_tactual = new QLabel(centralwidget);
        label_tactual->setObjectName(QString::fromUtf8("label_tactual"));
        label_tactual->setGeometry(QRect(10, 360, 51, 17));
        label_humedad = new QLabel(centralwidget);
        label_humedad->setObjectName(QString::fromUtf8("label_humedad"));
        label_humedad->setGeometry(QRect(230, 360, 51, 17));
        label_HUMEDAD = new QLabel(centralwidget);
        label_HUMEDAD->setObjectName(QString::fromUtf8("label_HUMEDAD"));
        label_HUMEDAD->setGeometry(QRect(290, 360, 69, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 384, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

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
        label_TMAX->setText(QString());
        label_TMIN->setText(QString());
        label_PREC->setText(QString());
        label_nriego->setText(QApplication::translate("MainWindow", "Nivel de riego:", nullptr));
        label_nluz->setText(QApplication::translate("MainWindow", "Nivel de luz:", nullptr));
        label_NRIEGO->setText(QString());
        label_NLUZ->setText(QString());
        iniciar->setText(QApplication::translate("MainWindow", "INICIAR", nullptr));
        label_TACTUAL->setText(QString());
        label_tactual->setText(QApplication::translate("MainWindow", "Temp:", nullptr));
        label_humedad->setText(QApplication::translate("MainWindow", "Humd:", nullptr));
        label_HUMEDAD->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
