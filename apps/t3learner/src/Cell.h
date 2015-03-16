/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QtGui>
#include <QtCore>

class Cell : public QGraphicsRectItem
{
private:
    int ID;
    int x, y;
    QColor color;
    int state;   
    
    // cell selection states
    enum eState
    {
         eCELL_FREE,        // not selected
         eCELL_AGENT,     // selected by agent
         eCELL_PLAYER     // selected by oponent player
    };

    enum eTurn
    {
         eTURN_AGENT,     // agent's turn
         eTURN_PLAYER     // player's turn
    };

 public:
    Cell(int ID, const QColor &color, int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget); 
   
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:    
    bool selectByPlayer();        
    bool selectByAgent();        
};

#endif	/* CELL_H */

