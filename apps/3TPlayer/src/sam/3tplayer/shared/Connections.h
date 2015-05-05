#ifndef __T3PLAYER_CONNECTIONS_H
#define __T3PLAYER_CONNECTIONS_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/utils/brooks/control.h"
#include "goon/utils/brooks/controlT.h"
#include "goon/utils/brooks/sensor.h"

#include "sam/3tplayer/data/structs.h"

namespace sam 
{
namespace t3player 
{
    
class Connections
{
    private:        
        // Field module
        goon::Control coAck;   
        goon::Sensor soBoardChanged;     
        // Move module
        goon::ControlT<Cell>coPickCell;   
        goon::Sensor soMoveDone;     
        
    public:
        Connections();
        //~Connections();
                

        // controls
        goon::Control& getCOAckBoardChanged() {return coAck;};        
        goon::ControlT<Cell>& getCOPickCell() {return coPickCell;};                
        
        // sensors
        goon::Sensor& getSOBoardChanged() {return soBoardChanged;}; 
        goon::Sensor& getSOMoveDone() {return soMoveDone;}; 
};

}
}    
#endif
