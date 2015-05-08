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


void Joint::init(int type, int length, int limit1, int limit2)
{
    // control proper argument values
    if (type < 0 || 
            type >= eJOINT_INVALID || 
            length < 0 ||
            limit1 >= limit2)
        return;

    this->type = type;
    this->length = length;
    this->limit1 = limit1;
    this->limit2 = limit2;
    this->rest = 0; // default
    benabled = true;
};

}
