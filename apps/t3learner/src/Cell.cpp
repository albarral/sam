/* 
 * File:   Cell.cpp
 * Author: ainoa
 * 
 * Created on March 12, 2015, 10:13 AM
 */

#include "Cell.h"

#include <QtGui>
#include <QtCore>
#include <QPainter>


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
        painter->setPen(Qt::cyan);
        painter->setFont(QFont("Arial", 90));
        painter->drawText(rect(), Qt::AlignCenter, "X");      
    }
    else if (state == Cell::eCELL_AGENT)
    {
        painter->setPen(Qt::cyan);
        painter->setFont(QFont("Arial", 90));
        painter->drawText(rect(), Qt::AlignCenter, "O");
    }  
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    
    int turn = Cell::eTURN_PLAYER;  // temporal (should be obtained from external Control object)
    
    // if players' turn & cell is free, select the cell (and show a mark)
    if (turn == Cell::eTURN_PLAYER)
    {
        if (selectByPlayer())
            update();
    }
    checkForWin();
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

void Cell::cleanAll(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // call base paint method
    QGraphicsRectItem::paint(painter, option, widget);
    
    painter->setPen(Qt::blue);
    painter->setFont(QFont("Arial", 90));       
    painter->drawText(rect(), Qt::AlignCenter, "");      
}

void Cell::checkForWin()
{
//    int cell1 = (Cell::ID==1);
    
    //horizontal lines
    
//    if(((Cell::ID==1)::state == (Cell::ID==2)::state) && ((Cell::ID==2)::state == (Cell::ID==3)::state) && ((Cell::ID==1)::state != 0));

    //vertical lines
    
    //diagonals
    
    //if( estado != libre && (cell1.estado == cell2.estado) && (cell1.estado == cell3.estado) )

    
}