#ifndef __SAM_BACKBONE_BONEMODUL_H
#define __SAM_BACKBONE_BONEMODUL_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{  
// Bean for TAB_MODULES    
class BoneModul
{
private:
    int area;                 // area ID
    int module;             // module ID
    std::string symbol;  // module symbol  (J1_MOV, J2_MOV, ... ) as defined in TAB_MODULES

public:    
    BoneModul(int area, int module, std::string symbol);
    ~BoneModul();

    int getArea() {return area;};
    int getModule() {return module;};
    std::string getSymbol() {return symbol;};
};
}
#endif
