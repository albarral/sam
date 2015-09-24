#ifndef __SAM_NETWORK_NETINTERPRETER_H
#define __SAM_NETWORK_NETINTERPRETER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <map>
#include <string>

#include "sam/network/data/AreaComponent.h"

namespace sam 
{
namespace network
{    
// Class used for the interpretation of SAM's network information on a specific SAM area.
// First its knowledge has to be defined (correspondences between network words & area info).
// Then its translator has to be built by using the list of predefined area components in network's language.
class NetInterpreter
{
private:
    bool benabled;          // true when the interpreter is ready to work 
    std::map<std::string, int> mapKnowledge;      // knowledge map <network word, area info value (numeric)> 
    std::map<int, int> mapTranslator;                  // translation map <network info number, area info value (numeric)>
    bool bknown;            // true when the translation is succesful
    int areaInfo;              // translated area info
    
public:
    NetInterpreter ();
    ~NetInterpreter();

    bool isEnabled() {return benabled;};
    
    // adds new item to knowledge map
    void addKnowledgeItem (std::string netWord, int areaInfo);    
    void clearKnowledge() {mapKnowledge.clear();};
    // builds translation map from list of predefined area components
    void buildTranslator(std::vector<AreaComponent>& listAreaComponents);    

    // translates the given network info to an area info. Return true if succesful.
    bool checkNetInfo(int netInfo);    
    bool isKnownInfo() {return bknown;}    
    int getAreaInfo() {return areaInfo;}
    
private:
    // search ID of a component specified by name
    int searchComponentByName(std::string netWord, std::vector<AreaComponent>& listAreaComponents);
};

}
}		
#endif
