/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   gabriel@migtron.com   *
 ***************************************************************************/

#include "Interface.h"
#include "ui_Interface.h"
#include "Cell.h"

#include <QMessageBox>
#include <iostream>
#include <stdlib.h> 
#include <vector>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QVector>
#include <QGraphicsPolygonItem>
#include <QtGui>


Interface::Interface(QMainWindow *parent) : QMainWindow(parent) {
    
    
    widget.setupUi(this);           
    
    connect(widget.startButton, SIGNAL(released()),this, SLOT(start()));
    connect(widget.userButton, SIGNAL(released()),this, SLOT(userWins()));
    connect(widget.agentButton, SIGNAL(released()),this, SLOT(agentWins()));
    connect(widget.drawButton, SIGNAL(released()),this, SLOT(draw()));    
    
    setScene();
   
}

void Interface::setScene(){
    scene = new QGraphicsScene(this);
    widget.boardView->setScene(scene);
    
    scene->setBackgroundBrush(QColor::fromRgb(128,128,128));
   
    QColor whitesmoke(QColor::fromRgb(245,245,245));
    QColor mediumblue(QColor::fromRgb(65,105,225));
    
    Cell *cell11 = new Cell(11, mediumblue, 0, 0);
    scene->addItem(cell11);
    Cell *cell12 = new Cell(12, whitesmoke, 111, 0);
    scene->addItem(cell12);
    Cell *cell13 = new Cell(13, mediumblue, 223, 0);
    scene->addItem(cell13);
    Cell *cell21 = new Cell(21, whitesmoke, 0, 111);
    scene->addItem(cell21);
    Cell *cell22 = new Cell(22, mediumblue, 111, 111);
    scene->addItem(cell22);
    Cell *cell23 = new Cell(23, whitesmoke, 223, 111);
    scene->addItem(cell23);
    Cell *cell31 = new Cell(31, mediumblue, 0, 223);
    scene->addItem(cell31);
    Cell *cell32 = new Cell(32, whitesmoke, 111, 223);
    scene->addItem(cell32);
    Cell *cell33 = new Cell(33, mediumblue, 223, 223);
    scene->addItem(cell33);
    
    widget.boardView->setScene(scene);            
}

void Interface::start(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Start", "Do you want to start the game?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        widget.boardView->setEnabled(true);
    } else {
        widget.boardView->setEnabled(false);
    }
}

void Interface::userWins(){
    QMessageBox msgBox;
    msgBox.setText("User wins this game!!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Interface::agentWins(){
    QMessageBox msgBox;
    msgBox.setText("Agent wins this game!!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Interface::draw(){
    QMessageBox msgBox;
    msgBox.setText("This game ends in draw!!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void Interface::play(){    
    /*while (positions.size() < 9 ){
        positions = randomMove(positions);
        userMove();
        
    }*/
}



/*std::vector<int> Interface::randomMove(std::vector<int> positions){
    
    int m_random = rand() % 9;
    while (positions[m_random] > 0){
        m_random = rand() % 9;
    }
    positions.erase(positions.begin()+m_random);
    positions.insert((positions.begin()+m_random),2);
    m_cont++;
    //markField(positions);
    return positions;
}*/
