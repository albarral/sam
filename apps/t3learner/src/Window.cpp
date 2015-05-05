/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "Window.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>

#include "Cell.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(QRect( -5, -5, 320, 360 ));
    scene->setBackgroundBrush(Qt::cyan);
    
    QColor color(Qt::white);
    // insert cells
    Cell *cell1 = new Cell (1, color, 0, 0);
    scene->addItem(cell1);    
    Cell *cell2 = new Cell (2, color, 105, 0);
    scene->addItem(cell2); 
    Cell *cell3 = new Cell (3, color, 210, 0);
    scene->addItem(cell3);    
    Cell *cell4 = new Cell (4, color, 0, 105);
    scene->addItem(cell4); 
    Cell *cell5 = new Cell (5, color, 105, 105);
    scene->addItem(cell5);    
    Cell *cell6 = new Cell (6, color, 210, 105);
    scene->addItem(cell6); 
    Cell *cell7 = new Cell (7, color, 0, 210);
    scene->addItem(cell7);    
    Cell *cell8 = new Cell (8, color, 105, 210);
    scene->addItem(cell8); 
    Cell *cell9 = new Cell (9, color, 210, 210);
    scene->addItem(cell9);    
   
    buttonIniciar = new QPushButton("Iniciar Partida");
    buttonIniciar->setGeometry(QRect(2.5, 320, 150, 30));
    scene->addWidget(buttonIniciar);
    
    connect(buttonIniciar, SIGNAL(released()), this, SLOT(clear()));
    
    buttonRecuperar = new QPushButton("Recuperar Partida");
    buttonRecuperar->setGeometry(QRect(157.5, 320, 150, 30));
    scene->addWidget(buttonRecuperar);
    
    connect(buttonRecuperar, SIGNAL(released()), this, SLOT(recuperar()));
    
    view = new QGraphicsView();
    view->setScene(scene);
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
}

void Window::clear()
{
//    Cell::cleanAll();
    
//    msgBox = new QMessageBox();  
//    msgBox->setText(QString("clear"));
//    msgBox->show();
}

void Window::recuperar()
{  
    msgBox = new QMessageBox();  
    msgBox->setText(QString("recuperar"));
    msgBox->show();
}
