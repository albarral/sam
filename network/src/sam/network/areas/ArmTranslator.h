#ifndef __SAM_NETWORK_ARMTRANSLATOR_H
#define __SAM_NETWORK_ARMTRANSLATOR_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <map>

#include "sam/network/data/NetworkCode.h"

namespace sam 
{
namespace network
{    
// Class used for the interpretation of network messages for the ARM area.
// It uses a dictionary obtained from DB table TAB_ARM_CODES.
// It holds IDs of modules, control actions & sensors.
class ArmTranslator
{
private:
    bool benabled;          // true when the translator is ready to work 
    std::map<std::string, int> mapCodes;    // map of network codes for the ARM area (<code name, code ID>)
public:
    static const int UNKNOWN_CODE = -1;     // unknown code indicator
    // modules
    int moduleJMOVER_1;
    int moduleJMOVER_2;
    int moduleJMOVER_3;
    int moduleJMOVER_4;
    int moduleJCONTROL_1;
    int moduleJCONTROL_2;
    int moduleJCONTROL_3;
    int moduleJCONTROL_4;
    int moduleJANGLE_1;
    int moduleJANGLE_2;
    int moduleJANGLE_3;
    int moduleJANGLE_4;
    // control actions
    int actionSTART;
    int actionSTOP;
    int actionJCONTROL_SPEED;
    int actionJMOVER_UP;
    int actionJMOVER_DOWN;
    int actionJMOVER_KEEP;
    int actionJMOVER_BRAKE;
    int actionJMOVER_STOP;
    // sensors info
    int senseJANGLE_IST_ANGLE;
    int senseJCONTROL_IST_SPEED;
    int senseJCONTROL_STATE;
    int senseJCONTROL_LIMIT_REACHED;
    int senseJMOVER_STATE;

public:
    ArmTranslator ();
    ~ArmTranslator();

    bool isEnabled() {return benabled;};
    
    // initializes the translator from the list of networks codes for this area
    void init (std::vector<NetworkCode>& listNetworkCodes);    
        
private:
    // builds the map of network codes for this area from a list of NetworkCode objects
    void buildMap (std::vector<NetworkCode>& listNetworkCodes);    
    // set this area's module IDs (using the codes map)
    void setAreaModules();
    // set this area's action IDs (using the codes map)
    void setAreaActions();
    // set this area's sensor IDs (using the codes map)
    void setAreaSensors();
    // Searches a code in the map by its name. If found its ID is returned, otherwise "unknown code" is returned
    int findMapCode(std::string codeName);
};

}
}		
#endif
