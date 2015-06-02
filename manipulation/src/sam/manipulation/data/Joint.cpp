/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "Joint.h"

namespace sam 
{
Joint::Joint ()
{
    benabled = false;
}

Joint::~Joint()
{
}

void Joint::init(manipulation::ParamsJoint& oParamsJoint)
{
    // control proper argument values
//    if (type < 0 || type >= eJOINT_INVALID ||        
    if (oParamsJoint.getLen() < 0 ||
        oParamsJoint.getLimit1() >= oParamsJoint.getLimit2())
        return;

    name = oParamsJoint.getJointName();
    length = oParamsJoint.getLen();
    limit1 = oParamsJoint.getLimit1();
    limit2 = oParamsJoint.getLimit2();
    rest = 0; // default
    benabled = true;
};

}
