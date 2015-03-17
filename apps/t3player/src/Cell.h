/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   gabriel@migtron.com   *
 ***************************************************************************/

#ifndef CELL_H
#define	CELL_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QMessageBox>
#include "Interface.h"

class Cell : public QGraphicsRectItem
{
    //std::vector<int> positions{std::vector<int>(9,0)};
public:
    Cell(int ID, const QColor &color, int x, int y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int ID;
    int x, y;
    QColor color;
    int state;
    QMessageBox* msgBox;    
       
    // cell selection states
    enum eState
    {
        eCELL_FREE,      // not selected
        eCELL_AGENT,     // selected by agent
        eCELL_PLAYER     // selected by oponent player
    };

    enum eTurn
    {
        eTURN_AGENT,     // agent's turn
        eTURN_PLAYER     // player's turn
    };
    
    bool selectByPlayer();
    bool selectByAgent();
    void setPosition(int ID);
    void randomMove();
};


#endif	/* CELL_H */

