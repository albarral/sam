#ifndef __SAM_DYNAMIC_MOVER_H
#define __SAM_DYNAMIC_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "JointMover.h"
//#include "goon/utils/Click.h"

namespace sam 
{
// A JointMover that makes dynamic movements
class DynamicMover : public JointMover
{
private:
 //   goon::Click oClick;

public:
        DynamicMover(Joint& oJoint);
        ~DynamicMover();
};
}
#endif
