/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   gabriel@migtron.com   *
 ***************************************************************************/

#ifndef _INTERFACE_H
#define	_INTERFACE_H

#include "ui_Interface.h"
#include <QPushButton>
#include <iostream>
#include <vector>
#include <QMouseEvent>
#include <QMessageBox>

#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsRectItem>
#include<QVector>
#include<QGraphicsPolygonItem>

#include<QGraphicsSceneMouseEvent>

class Interface : public QMainWindow {
    Q_OBJECT
    
    public:
        Interface(QMainWindow *parent = 0);

    private:
        Ui::Interface widget;
        QGraphicsScene *scene;
        QGraphicsView *view;
        QGraphicsPolygonItem *polygon;
        QGraphicsRectItem *rectangle;
    
    private slots:
        void start();
        void userWins();
        void agentWins();
        void draw();
        
        void play();
        void setScene();
        //std::vector<int> randomMove(std::vector<int> positions);
};


#endif	/* _INTERFACE_H */
