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
// Base class for management of backbone communication.
// It handles connections to the backbone DB. 
// It tunes to one of the messages table & to a specific sam's area.
// Calls to init() and tune() need to be done to use it.    
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
    bool btuned;                              // indicates we are tuned to a table & area  
    backbone::Config oConfig;
    DatabaseClient oDBClient;          // handler for database connections
    std::string tabAreas;                 // DB table for supported areas
    std::string tabModules;              // DB table for supported modules
    std::string tabMessages;           // DB table for communication messages (input or output)
    int tunedAreaID;                        // area to which we are tuned
    std::vector<BoneArea> listAreas;        // list of areas supported (read from tabAreas)
    std::vector<BoneModul> listModules;   // list of modules supported (read from tabModules)

public:
    BoneBase();
    
    // sets connection parameters for the database client handler
    void init ();
    // Tunes reader/writer to the commands or info table & to the specifed area
    virtual void tune(int direction, std::string area);  
    // Checks if init & tune have already been called
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
