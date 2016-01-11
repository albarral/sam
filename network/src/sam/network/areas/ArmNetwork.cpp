/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "ArmNetwork.h"

namespace sam
{
namespace network
{ 
// Constructor 
ArmNetwork::ArmNetwork ()
{           
    benabled = false;
    bknown = false;
}

void ArmNetwork::addElement(std::string networkCodename, int areaCode)
{
    mapDictionary.emplace(networkCodename, areaCode);
    
    // disable interpreter till map translation is rebuilt
    if (benabled)
        benabled = false;
}

void ArmNetwork::updateTranslator(std::vector<NetworkCode>& listNetworkCodes)
{
    // For each element in the dictionary: 
    // search its corresponding code ID and replicate it the translation map with its numeric value

    // first clear the translation map
    mapTranslate.clear();

    // then do the search
    int networkCodeID;
    for (auto& element: mapDictionary)
    {
        networkCodeID = searchCodeByName(element.first, listNetworkCodes);
        // if found, add translation element
        if (networkCodeID != -1)
            mapTranslate.emplace(networkCodeID, element.second);            
    }        
    
    // enable interpreter if we have a filled translation map
    if (mapTranslate.size() > 0)
        benabled = true;
}

int ArmNetwork::searchCodeByName(std::string codename, std::vector<NetworkCode>& listNetworkCodes)
{
    int codeID = -1;
    // walk the list of components searching for the given name
    for (auto& networkCode : listNetworkCodes)
    {
        // if component found, store its ID & quit search
        if (codename.compare(networkCode.getName()) == 0)
        {
            codeID = networkCode.getID();
            break;
        }
    }

    return codeID;
}

bool ArmNetwork::translateNetworkCode(int networkCodeID)
{
    std::map<int, int>::iterator it_translation; 
    
    // search network info in translation map
    it_translation = mapTranslate.find(networkCodeID);
    // if found, store corresponding area info 
    if (it_translation != mapTranslate.end())
    {
        bknown = true;
        areaCode = it_translation->second;        
    }
    else 
        bknown = false;
    
    return bknown;
}

}
}