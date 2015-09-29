#ifndef __SAM_NETWORK_NETINTERPRETER_H
#define __SAM_NETWORK_NETINTERPRETER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <map>
#include <string>

#include "sam/network/data/NetworkCode.h"

namespace sam 
{
namespace network
{    
// Class used for the interpretation of network messages for a specific SAM area.
// First a dictionary for the interpreter has to be defined: each network code name for the area and its corresponding meaning (action, sensor or module) in this area.
// Then a translation map is built from the dictionary with the numeric correspondences (as only numeric values will travel through SAM's network)
class NetInterpreter
{
private:
    bool benabled;          // true when the interpreter is ready to work 
    std::map<std::string, int> mapDictionary;      // dictionary <network code name, area code number> 
    std::map<int, int> mapTranslate;                // translation map <network code number, area code number>
    bool bknown;            // true when the translation is succesful
    int areaCode;           // translated area code
    
public:
    NetInterpreter ();
    ~NetInterpreter();

    bool isEnabled() {return benabled;};
    
    // adds new item to the interpreters dictionary
    void addElement (std::string networkCodename, int areaCode);    
    void clearDictionary() {mapDictionary.clear();};
    // builds translation map from list of predefined area components
    void updateTranslator(std::vector<NetworkCode>& listNetworkCodes);    

    // translates the given network info to an area info. Return true if succesful.
    bool translateNetworkCode(int netInfo);    
    bool isKnownCode() {return bknown;}    
    int getAreaCode() {return areaCode;}
    
private:
    // search the code number for a specified by codename
    int searchCodeByName(std::string codename, std::vector<NetworkCode>& listNetworkCodes);
};

}
}		
#endif
