#ifndef __SAM_BACKBONE_BONEBASE_H
#define __SAM_BACKBONE_BONEBASE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "config/Config.h"
#include "data/BoneArea.h"
#include "data/BoneModul.h"
#include "utils/DatabaseClient.h"

namespace sam 
{
// Base class for handling backbone data. Manages connections with backbone database.
// Must be initialized & tuned before using it.    
class BoneBase
{
public:
    enum eDirection 
    {
        eTAB_COMMANDS,  // connect to commands table (input to SAM)
        eTAB_INFO,            // connect to info table (output from SAM) 
        eTAB_DIM
    };
    
protected:
    bool binitialized;
    bool btuned;                              // indicates the reader/writer is tuned to a specific table & an area  
    backbone::Config oConfig;
    DatabaseClient oDBClient;          // handler for database clients
    std::string tabAreas;                 // DB table storing the areas supported by backbone system
    std::string tabModules;              // DB table storing the modules supported by backbone system
    std::string tabMessages;           // DB table storing the messages (between backbone & external system) (TAB_INFO for backbone outputs, TAB_COMMANDS for backbone inputs)
    int myAreaID;                            // area to which the reader/writer will be tuned
    std::vector<BoneArea> listAreas;        // list of areas supported in backbone system (those in TAB_AREAS) (navigation, manipulation ...)
    std::vector<BoneModul> listModules;   // list of modules supported in backbone system (those in TAB_MODULES) (elbow mover, ...) 

public:
    BoneBase();
    
    // sets connection parameters for the database client handler
    void init ();
    // Tunes reader/writer to the commands or info table & to the specifed area
    virtual void tune(int direction, std::string area);  
    bool isReady() {return (binitialized && btuned);};
        
    std::vector<BoneArea>& getListAreas() {return listAreas;}
    std::vector<BoneModul>& getListModules() {return listModules;}

    // closes connection to DB
    void close();   

protected:
    // add initial & final quotes to a given string
    std::string stringQuotes(std::string word) {return "'"+word+"'";};
private:
    // reads from DB the list of supported SAM areas
    void readSupportedAreas();
    // reads from DB the list of supported SAM modules
    void readSupportedModules();
    // Obtains the ID of the specified area name, returns 0 if not found. 
    int searchAreaID(std::string area);
    // Obtains the ID of the specified module name (inside given area) , returns 0 if not found. 
    int searchModuleID(int areaID, std::string module);
    
};
}

#endif
