#ifndef __SAM_BACKBONE_BONEAREA_H
#define __SAM_BACKBONE_BONEAREA_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
class BoneArea
{    
private:
    int ID;                         // area ID
    std::string area;          // subsystem name (manipulation, navigation ...)

public:    
    BoneArea(int ID, std::string area);
    ~BoneArea();

    int getID() {return ID;};
    std::string getArea() {return area;};
};
}
#endif
