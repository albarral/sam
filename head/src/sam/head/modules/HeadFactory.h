#ifndef __SAM_HEAD_HEADFACTORY_H
#define __SAM_HEAD_HEADFACTORY_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "sam/head/modules/Head.h"

namespace sam 
{
namespace head
{    
// Class to create a specific Head object
class HeadFactory
{
private:
    static log4cxx::LoggerPtr logger;

public:
    enum eOption
    {
        eHEAD_UNDEFINED,
        eHEAD_IPCAMERA1,
        eHEAD_IPCAMERA2,
        eHEAD_DIM
    };

    // factory method to create different types of Head objects
    static Head* createHead (int option);
};

}
}
#endif
