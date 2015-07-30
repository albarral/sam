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
#include "data/BoneSymbol.h"
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
        eTAB_CONTROL,       // connect to control table (commands sent to SAM modules)
        eTAB_SENSE,           // connect to sense table (states info shared by SAM modules) 
        eTAB_DIM
    };
    const int areaGeneralSymbol = 0;   // area field for general symbols (valid for all areas)
    
protected:
    bool binitialized;
    bool btuned;                              // indicates we are tuned to a table & area  
    backbone::Config oConfig;
    DatabaseClient oDBClient;          // handler for database connections
    std::string tabAreas;                 // DB table for supported areas
    std::string tabModules;              // DB table for supported modules
    std::string tabSymbols;             // DB table for supported symbols (control & sense categories)
    std::string tabMessages;           // DB table for message communications (control or sense)
    int tunedArea;                        // area to which we are tuned

public:
    BoneBase();
    
    // sets connection parameters for the database client handler
    void init ();
    // tunes the reader/writer to the commands or info table & to the specified area
    virtual void tune(int direction, std::string areaName);  
    // Checks if init & tune have already been called
    bool isReady() {return (binitialized && btuned);};
        
    // gets from DB the list of supported areas (the list is returned)
    std::vector<BoneArea> readAreas();
    // gets from DB the list of modules of the tuned area (the list is returned)
    std::vector<BoneModul> readAreaModules();
    // gets from DB the list of CONTROL symbols for the tuned area & for general use (the list is returned)
    std::vector<BoneSymbol> readAreaControls();
    // gets from DB the list of SENSOR symbols for the tuned area & for general use (the list is returned)
    std::vector<BoneSymbol> readAreaSensors();
    
    // searches in DB for the area with the specified name. Return its ID if found, or 0 otherwise.
    int searchAreaByName(std::string name);

    // closes connection to DB
    void close();   

protected:    
     // add initial & final quotes to a given string
    std::string addQuotes(std::string word) {return "'"+word+"'";};
private:
    // gets from DB the list of symbols of the specified category for the tuned area (the list is returned)
    std::vector<BoneSymbol> readAreaSymbols(int category);

};
}

#endif
