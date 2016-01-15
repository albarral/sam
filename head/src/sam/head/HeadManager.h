#ifndef __SAM_APP_PLAYER_H
#define __SAM_APP_PLAYER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/head/modules/HeadController.h"
#include "sam/network2/NetworkUser.h"

namespace sam 
{
namespace head
{  
class HeadManager : public network::NetworkUser
{
private:
    static log4cxx::LoggerPtr logger;
    // modules
    HeadController oHeadController;
    
public:
    HeadManager();
    ~HeadManager();
        
    void startModules();
    void stopModules();
};

}
}
#endif
