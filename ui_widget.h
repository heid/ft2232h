/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QComboBox *cbDevices;
    QPushButton *btnOpen;
    QLabel *lblReadingSpeed;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(290, 151);
        cbDevices = new QComboBox(Widget);
        cbDevices->setObjectName(QString::fromUtf8("cbDevices"));
        cbDevices->setGeometry(QRect(20, 20, 161, 21));
        btnOpen = new QPushButton(Widget);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));
        btnOpen->setGeometry(QRect(190, 20, 80, 21));
        lblReadingSpeed = new QLabel(Widget);
        lblReadingSpeed->setObjectName(QString::fromUtf8("lblReadingSpeed"));
        lblReadingSpeed->setGeometry(QRect(110, 90, 71, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btnOpen->setText(QCoreApplication::translate("Widget", "Open", nullptr));
        lblReadingSpeed->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
