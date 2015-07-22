#ifndef __SAM_BACKBONE_BONEWRITER_H
#define __SAM_BACKBONE_BONEWRITER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>

#include "BoneBase.h"

namespace sam 
{
// Utility class for wrintting Backbone data. 
// Writes messages to a specific DB table & about a specific sam's area
// Extends from BoneBase class.    
class BoneWriter : public BoneBase
{
//private:    
public:
    BoneWriter();
        
    // write given coms message in    
    void write (int moduleID, std::string info, int detail);
    
};
}

#endif
