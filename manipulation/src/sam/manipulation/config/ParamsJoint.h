#ifndef __SAM_MANIPULATION_PARAMSJOINT_H
#define __SAM_MANIPULATION_PARAMSJOINT_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
namespace manipulation 
{
// Config params for Joint class
class ParamsJoint 
{
   private:                
        std::string jointName;
        int limit1; // lower limit (degrees)
        int limit2; // upper limit (degrees)
        int len; // length of arm section (cm)        
        
    public:
        ParamsJoint();

        void set(std::string jointName, int limit1, int limit2, int length) {this->jointName = jointName; this->limit1 = limit1; this->limit2 = limit2; len = length;}

        std::string& getJointName() {return jointName;};
        int getLimit1() {return limit1;};
        int getLimit2() {return limit2;};
        int getLen() {return len;};        
};

}
}    
#endif
