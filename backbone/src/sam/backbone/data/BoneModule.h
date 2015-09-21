#ifndef __SAM_BACKBONE_BONEMODULE_H
#define __SAM_BACKBONE_BONEMODULE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{  
namespace backbone 
{
// Bean for TAB_XXX_MODULES    
class BoneModule
{
private:
    int ID;                 // module ID
    std::string name;             // module name
    std::string description;  // module description

public:    
    BoneModule(int ID, std::string name, std::string desc);
    ~BoneModule();

    int getID() {return ID;};
    std::string getName() {return name;};
    std::string getDescription() {return description;};
};

}
}
#endif
