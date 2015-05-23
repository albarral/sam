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

void Joint::init(int type, manipulation::ParamsJoint& oParamsJoint)
{
    // control proper argument values
    if (type < 0 || type >= eJOINT_INVALID ||        
            oParamsJoint.getLen() < 0 ||
            oParamsJoint.getLimit1() >= oParamsJoint.getLimit2())
        return;

    this->type = type;
    this->length = oParamsJoint.getLen();
    this->limit1 = oParamsJoint.getLimit1();
    this->limit2 = oParamsJoint.getLimit2();
    this->rest = 0; // default
    benabled = true;
};

}
