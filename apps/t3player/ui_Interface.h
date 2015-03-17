/********************************************************************************
** Form generated from reading UI file 'Interface.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QWidget *centralwidget;
    QPushButton *startButton;
    QPushButton *userButton;
    QPushButton *agentButton;
    QPushButton *drawButton;
    QGraphicsView *boardView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QString::fromUtf8("Interface"));
        Interface->resize(370, 497);
        centralwidget = new QWidget(Interface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(40, 400, 98, 27));
        userButton = new QPushButton(centralwidget);
        userButton->setObjectName(QString::fromUtf8("userButton"));
        userButton->setGeometry(QRect(230, 370, 98, 27));
        agentButton = new QPushButton(centralwidget);
        agentButton->setObjectName(QString::fromUtf8("agentButton"));
        agentButton->setGeometry(QRect(230, 400, 98, 27));
        drawButton = new QPushButton(centralwidget);
        drawButton->setObjectName(QString::fromUtf8("drawButton"));
        drawButton->setGeometry(QRect(230, 430, 98, 27));
        boardView = new QGraphicsView(centralwidget);
        boardView->setObjectName(QString::fromUtf8("boardView"));
        boardView->setGeometry(QRect(20, 20, 331, 331));
        Interface->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Interface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Interface->setStatusBar(statusbar);

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "Interface", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("Interface", "Start", 0, QApplication::UnicodeUTF8));
        userButton->setText(QApplication::translate("Interface", "User wins", 0, QApplication::UnicodeUTF8));
        agentButton->setText(QApplication::translate("Interface", "Agent wins", 0, QApplication::UnicodeUTF8));
        drawButton->setText(QApplication::translate("Interface", "Draw", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
