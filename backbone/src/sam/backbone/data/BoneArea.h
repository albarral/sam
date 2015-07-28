#ifndef __SAM_BACKBONE_BONEAREA_H
#define __SAM_BACKBONE_BONEAREA_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
// Bean for TAB_AREAS
class BoneArea
{    
private:
    int area;                       // area ID
    std::string name;          // subsystem name (manipulation, navigation ...)

public:    
    BoneArea(int area, std::string name);
    ~BoneArea();

    int getArea() {return area;};
    std::string getName() {return name;};
};
}
#endif
