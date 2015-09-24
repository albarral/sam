/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "NetInterpreter.h"

namespace sam
{
namespace network
{ 
// Constructor 
NetInterpreter::NetInterpreter ()
{           
    benabled = false;
    bknown = false;
}

void NetInterpreter::addKnowledgeItem(std::string netWord, int areaInfo)
{
    mapKnowledge.emplace(netWord, areaInfo);
    
    // disable interpreter till map translation is rebuilt
    if (benabled)
        benabled = false;
}

void NetInterpreter::buildTranslator(std::vector<AreaComponent>& listAreaComponents)
{
    // For each element in knowledge map: search corresponding numeric info for the component's name.
    // Then replicate the element in the translation map, but with its numeric network value instead of the word.

    // first clear the translation map
    mapTranslator.clear();

    // then do the search
    int componentID;
    for (auto& element: mapKnowledge)
    {
        componentID = searchComponentByName(element.first, listAreaComponents);
        // if found, add translation element
        if (componentID != -1)
            mapTranslator.emplace(componentID, element.second);            
    }        
    
    // enable interpreter if we have a filled translation map
    if (mapTranslator.size() > 0)
        benabled = true;
}

int NetInterpreter::searchComponentByName(std::string netWord, std::vector<AreaComponent>& listAreaComponents)
{
    int componentID = -1;
    // walk the list of components searching for the given name
    for (auto& component : listAreaComponents)
    {
        // if component found, store its ID & quit search
        if (netWord.compare(component.getName()) == 0)
        {
            componentID = component.getID();
            break;
        }
    }

    return componentID;
}

bool NetInterpreter::checkNetInfo(int netInfo)
{
    std::map<int, int>::iterator it_translation; 
    
    // search network info in translation map
    it_translation = mapTranslator.find(netInfo);
    // if found, store corresponding area info 
    if (it_translation != mapTranslator.end())
    {
        bknown = true;
        areaInfo = it_translation->second;        
    }
    else 
        bknown = false;
    
    return bknown;
}

}
}