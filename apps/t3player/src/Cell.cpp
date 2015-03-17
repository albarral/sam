/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   gabriel@migtron.com   *
 ***************************************************************************/

#include "Cell.h"
#include "Interface.h"

#include <vector>
#include <QtGui>
#include <iostream>

class Turn{
public:
    static int turn;
    static std::vector<int> positions;
};
int Turn::turn = 1;
std::vector<int> Turn::positions(9,0);

Cell::Cell(int ID, const QColor &color, int x, int y)
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->color = color;
    state = Cell::eCELL_FREE;
        
    this->setRect(x, y, 105, 105);
    setBrush(color);
    
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    setPen(blackpen);
}

void Cell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    //call base paint method
    QGraphicsRectItem::paint(painter, option, widget);
    
    if(state == Cell::eCELL_PLAYER)
    {       
        painter->setPen(Qt::black);
        painter->setFont(QFont("Courier", 70));
        painter->drawText(rect(), Qt::AlignCenter, "X");        
    }
    else if(state == Cell::eCELL_AGENT)
    {
        painter->setPen(Qt::red);
        painter->setFont(QFont("Courier", 70));
        painter->drawText(rect(), Qt::AlignCenter, "O");        
    }
}

// shows a message when item is clicked
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
    
    Turn player;
    
    //int turn = Cell::eTURN_PLAYER;
    if(player.turn == Cell::eTURN_PLAYER){
        if(selectByPlayer()){
            update();
        }
        player.turn = 0;
    }
    
    else if(player.turn == Cell::eTURN_AGENT){
        if(selectByAgent()){
            update();
        }
        
        player.turn = 1;
    }
    setPosition(ID);
    
    for(std::vector<int>::const_iterator i = player.positions.begin(); i != player.positions.end(); i++){
        std::cout << *i << ' ';        
    }
    std::cout << std::endl;
}

// Selects by player if cell is free. Returns true if state changed, false otherwise
bool Cell::selectByPlayer(){
    if (state == Cell::eCELL_FREE){
        state = Cell::eCELL_PLAYER;
        return true;
    }else{
        return false;
    }
}

// Selects by agent if cell is free. Returns true if state changed, false otherwise
bool Cell::selectByAgent(){
    if (state == Cell::eCELL_FREE){
        state = Cell::eCELL_AGENT;
        return true;
    }else{
        return false;
    }
}

void Cell::randomMove(){
    Turn player;
    
    int m_random = rand() % 9;
    while (player.positions[m_random] > 0){
        m_random = rand() % 9;
    }
    
    player.positions.erase(player.positions.begin()+m_random);
    player.positions.insert((player.positions.begin()+m_random),2);
    //m_cont++;
    //markField(positions);
}

void Cell::setPosition(int ID){
    Turn player;
    
    if(ID == 11){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin());
            player.positions.insert((player.positions.begin()),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin());
            player.positions.insert((player.positions.begin()),2);
        }
    }else if(ID == 12){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+1);
            player.positions.insert((player.positions.begin()+1),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+1);
            player.positions.insert((player.positions.begin()+1),2);
        }
    }else if(ID == 13){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+2);
            player.positions.insert((player.positions.begin()+2),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+2);
            player.positions.insert((player.positions.begin()+2),2);
        }
    }else if(ID == 21){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+3);
            player.positions.insert((player.positions.begin()+3),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+3);
            player.positions.insert((player.positions.begin()+3),2);
        }
    }else if(ID == 22){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+4);
            player.positions.insert((player.positions.begin()+4),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+4);
            player.positions.insert((player.positions.begin()+4),2);
        }
    }else if(ID == 23){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+5);
            player.positions.insert((player.positions.begin()+5),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+5);
            player.positions.insert((player.positions.begin()+5),2);
        }
    }else if(ID == 31){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+6);
            player.positions.insert((player.positions.begin()+6),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+6);
            player.positions.insert((player.positions.begin()+6),2);
        }
    }else if(ID == 32){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+7);
            player.positions.insert((player.positions.begin()+7),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+7);
            player.positions.insert((player.positions.begin()+7),2);
        }
    }else if(ID == 33){
        if(player.turn == 1){
            player.positions.erase(player.positions.begin()+8);
            player.positions.insert((player.positions.begin()+8),1);
        } else if(player.turn == 0){
            player.positions.erase(player.positions.begin()+8);
            player.positions.insert((player.positions.begin()+8),2);
        }
    }
}