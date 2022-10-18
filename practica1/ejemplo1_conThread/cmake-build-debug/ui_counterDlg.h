/********************************************************************************
** Form generated from reading UI file 'counterDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTERDLG_H
#define UI_COUNTERDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Counter
{
public:
    QPushButton *button;
    QLCDNumber *lcdNumber;
    QPushButton *start;
    QPushButton *reset;
    QSlider *sliderPeriodo;
    QPushButton *decrementar;

    void setupUi(QWidget *Counter)
    {
        if (Counter->objectName().isEmpty())
            Counter->setObjectName(QString::fromUtf8("Counter"));
        Counter->resize(400, 300);
        button = new QPushButton(Counter);
        button->setObjectName(QString::fromUtf8("button"));
        button->setGeometry(QRect(240, 170, 111, 71));
        lcdNumber = new QLCDNumber(Counter);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(50, 40, 301, 91));
        start = new QPushButton(Counter);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(70, 170, 101, 71));
        reset = new QPushButton(Counter);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(160, 260, 89, 25));
        sliderPeriodo = new QSlider(Counter);
        sliderPeriodo->setObjectName(QString::fromUtf8("sliderPeriodo"));
        sliderPeriodo->setGeometry(QRect(20, 120, 16, 160));
        sliderPeriodo->setOrientation(Qt::Vertical);
        decrementar = new QPushButton(Counter);
        decrementar->setObjectName(QString::fromUtf8("decrementar"));
        decrementar->setGeometry(QRect(160, 140, 89, 25));

        retranslateUi(Counter);

        QMetaObject::connectSlotsByName(Counter);
    } // setupUi

    void retranslateUi(QWidget *Counter)
    {
        Counter->setWindowTitle(QCoreApplication::translate("Counter", "Counter", nullptr));
        button->setText(QCoreApplication::translate("Counter", "STOP", nullptr));
        start->setText(QCoreApplication::translate("Counter", "START", nullptr));
        reset->setText(QCoreApplication::translate("Counter", "reset", nullptr));
        decrementar->setText(QCoreApplication::translate("Counter", "Inversor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Counter: public Ui_Counter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTERDLG_H
