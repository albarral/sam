#ifndef __SAM_NETWORK_DBAREACODES_H
#define __SAM_NETWORK_DBAREACODES_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "sam/utils2/DBConnection.h"
#include "sam/network/data/NetworkCode.h"

namespace sam 
{
namespace network 
{
// Class used for reading the CODES table for a network's area
// Extends from DBConnection    
class DBAreaCodes : public utils2::DBConnection
{
private:        
    bool btuned;                            // flag to indicate the target table is set
    std::string tabAreaCodes;           // name of CODES table
    std::vector<NetworkCode> listAreaCodes;    // list of network codes for an area
    std::string selectAreaCodes;                 // query for selecting the area modules
    
public:
    DBAreaCodes();
    
    // Sets the target table name
    void tune2Table(std::string tabName);
    bool isTuned() {return btuned;};        

    // Reads all network codes from table. Returns true if ok, false otherwise.
    bool readAreaCodes();

    // Returns the list of area codes
    std::vector<network::NetworkCode>& getListAreaCodes() {return listAreaCodes;}
};
}
}
#endif
