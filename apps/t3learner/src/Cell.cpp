/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <QtGui>
#include <QtCore>
#include <QPainter>

#include "Cell.h"

Cell::Cell(int ID, const QColor &color, int x, int y) 
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->color = color;   
    // cell is initially unselected
    state = Cell::eCELL_FREE;
   
    this->setRect(x, y, 100, 100);
    setBrush(color);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // call base paint method
    QGraphicsRectItem::paint(painter, option, widget);
    
    if (state == Cell::eCELL_PLAYER)
    {
        painter->setPen(Qt::blue);
        painter->setFont(QFont("Arial", 30));
        painter->drawText(rect(), Qt::AlignCenter, "X");        
    }
    else if (state == Cell::eCELL_AGENT)
    {
        painter->setPen(Qt::blue);
        painter->setFont(QFont("Arial", 30));
        painter->drawText(rect(), Qt::AlignCenter, "O");        
    }    
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // call base mousePressEvent method
    QGraphicsItem::mousePressEvent(event);
   
    int turn = Cell::eTURN_PLAYER;  // temporal (should be obtained from external Control object)
    
    // if players' turn & cell is free, select the cell (and show a mark)
    if (turn == Cell::eTURN_PLAYER)
    {
        if (selectByPlayer())
            update();
    }        
}

// Selects by player if cell is free. Returns true if state changed, false otherwise
bool Cell::selectByPlayer()
{
    if (state == Cell::eCELL_FREE)
    {
      state = Cell::eCELL_PLAYER;
      return true;
    }
    else        
        return false;
}

// Selects by agent if cell is free. Returns true if state changed, false otherwise
bool Cell::selectByAgent()
{
    if (state == Cell::eCELL_FREE)
    {
      state = Cell::eCELL_AGENT;
      return true;
    }
    else        
        return false;
}
