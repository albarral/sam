#ifndef __SAM_BACKBONE_BONEBASE_H
#define __SAM_BACKBONE_BONEBASE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "utils/DatabaseClient.h"
#include "data/BoneArea.h"
#include "data/BoneModul.h"

namespace sam 
{
// Base class for handling backbone data. Manages connections with backbone database.
// Must be initialized & tuned before using it.    
class BoneBase
{
protected:
    bool binitialized;
    bool btuned;                              // indicates the reader/writer is tuned to a specific table & an area                
    DatabaseClient oDBClient;          // handler for database clients
    std::string tabAreas;                 // DB table in which Sam areas are defined
    std::string tabModules;              // DB table in which Sam modules are defined
    std::string tabMessages;           // DB table used for transferring the messages (TAB_INFO or TAB_COMMANDS)
    int myAreaID;                            // area to which the reader/writer will be tuned
    std::vector<BoneArea> listAreas;        // list of areas as defined in DB (navigation, manipulation ...)
    std::vector<BoneModul> listModules;   // list of modules as defined in DB (elbow mover, ...) 

public:
    BoneBase();
    
    // sets connection parameters for the database client handler
    void init (std::string url, std::string user, std::string password, std::string schema);
    // Tunes reader/writer to table & area
    virtual void tune(std::string tabMessages, std::string area);  
    bool isReady() {return (binitialized && btuned);};
        
    std::vector<BoneArea>& getListAreas() {return listAreas;}
    std::vector<BoneModul>& getListModules() {return listModules;}

    // closes connection to DB
    void close();   

protected:
    // add initial & final quotes to a given string
    std::string stringQuotes(std::string word) {return "'"+word+"'";};
private:
    void readAreas();
    void readModules();
    // Obtains the ID of the specified area name, returns 0 if not found. 
    int searchAreaID(std::string area);
    // Obtains the ID of the specified module name (inside given area) , returns 0 if not found. 
    int searchModuleID(int areaID, std::string module);
    
};
}

#endif
