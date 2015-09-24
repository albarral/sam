#ifndef __SAM_BACKBONE_AREACONNECTION_H
#define __SAM_BACKBONE_AREACONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BoneConnection.h"
#include "sam/network/data/AreaComponent.h"

namespace sam 
{
namespace backbone 
{
// Class used for reading the backbone COMPONENTS table for an area
// Extends from BoneConnection    
class AreaConnection : public BoneConnection
{
private:        
    bool btuned;                            // flag to indicate the target table is set
    std::string tabComponents;      // name of COMPONENTS table
    std::vector<network::AreaComponent> listModules;    // list of area modules
    std::vector<network::AreaComponent> listControls;     // list of area controls
    std::vector<network::AreaComponent> listSensors;    // list of area sensors
    std::string selectModules;                 // query for selecting the area modules
    std::string selectControls;                 // query for selecting the area modules
    std::string selectSensors;                 // query for selecting the area modules
    
public:
    AreaConnection();
    
    // Sets the target table name
    void tune2Table(std::string tabName);
    bool isTuned() {return btuned;};        

    // Reads all components from table. Returns true if ok, false otherwise.
    bool readAreaComponents();

    // Returns the list of area modules
    std::vector<network::AreaComponent>& getListModules() {return listModules;}
    // Returns the list of area controls
    std::vector<network::AreaComponent>& getListControls() {return listControls;}
    // Returns the list of area sensors
    std::vector<network::AreaComponent>& getListSensors() {return listSensors;}    
};
}
}
#endif
