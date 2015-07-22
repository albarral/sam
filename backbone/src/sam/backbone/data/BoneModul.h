#ifndef __SAM_BACKBONE_BONEMODUL_H
#define __SAM_BACKBONE_BONEMODUL_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
class BoneModul
{
private:
    int areaID;                 
    int moduleID;  
    std::string module;       // module name  (ShoulderMover, ElbowMover, ...)

public:    
    BoneModul(int areaID, int moduleID, std::string module);
    ~BoneModul();

    int getAreaID() {return areaID;};
    int getModuleID() {return moduleID;};
    std::string getModule() {return module;};
};
}
#endif
