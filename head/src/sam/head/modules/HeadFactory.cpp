/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "sam/head/modules/HeadFactory.h"
#include "sam/head/modules/IPCamHead.h"

using namespace log4cxx;

namespace sam 
{
namespace head
{    
LoggerPtr HeadFactory::logger(Logger::getLogger("sam.head"));

Head* HeadFactory::createHead(int option)
{
    Head* oHead;
        
    switch (option)
    {
        case eHEAD_IPCAMERA1:                        
            LOG4CXX_INFO(logger, "Head = IP camera 1");
            oHead = new IPCamHead("http://192.168.1.2/PANTILTCONTROL.CGI", 80);
            oHead->setPanRange(-170, 170);
            oHead->setPanOffset(170);
            oHead->setTiltRange(-45, 90);
            oHead->setTiltOffset(45);
            break;
            
        case eHEAD_IPCAMERA2:                        
            LOG4CXX_INFO(logger, "Head = IP camera 2");
            oHead = new IPCamHead("http://192.168.1.3/PANTILTCONTROL.CGI", 80);
            oHead->setPanRange(-170, 170);
            oHead->setPanOffset(170);
            oHead->setTiltRange(-45, 90);
            oHead->setTiltOffset(45);
            break;

        default:
            oHead = NULL;
    }

    return oHead;
}

}
}
