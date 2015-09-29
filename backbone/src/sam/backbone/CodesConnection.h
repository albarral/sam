#ifndef __SAM_BACKBONE_CODESCONNECTION_H
#define __SAM_BACKBONE_CODESCONNECTION_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "BaseConnection.h"
#include "sam/network/data/NetworkCode.h"

namespace sam 
{
namespace backbone 
{
// Class used for reading the backbone CODES table for an area
// Extends from BaseConnection    
class CodesConnection : public BaseConnection
{
private:        
    bool btuned;                            // flag to indicate the target table is set
    std::string tabNetworkCodes;      // name of CODES table
    std::vector<network::NetworkCode> listNetModules;    // list of area modules
    std::vector<network::NetworkCode> listNetControls;     // list of area controls
    std::vector<network::NetworkCode> listNetSensors;    // list of area sensors
    std::string selectNetModules;                 // query for selecting the area modules
    std::string selectNetControls;                 // query for selecting the area modules
    std::string selectNetSensors;                 // query for selecting the area modules
    
public:
    CodesConnection();
    
    // Sets the target table name
    void tune2Table(std::string tabName);
    bool isTuned() {return btuned;};        

    // Reads all network codes from table. Returns true if ok, false otherwise.
    bool readNetworkCodes();

    // Returns the list of area modules
    std::vector<network::NetworkCode>& getListModules() {return listNetModules;}
    // Returns the list of area controls
    std::vector<network::NetworkCode>& getListControls() {return listNetControls;}
    // Returns the list of area sensors
    std::vector<network::NetworkCode>& getListSensors() {return listNetSensors;}    
};
}
}
#endif
