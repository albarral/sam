/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "BoneBase.h"

#include <cppconn/resultset.h>

namespace sam 
{
BoneBase::BoneBase() 
{
    binitialized = false;
    btuned = false;
}

void BoneBase::init()
{
    // sets database connection params
    oDBClient.init(oConfig.getDBServerUrl(), oConfig.getDBUser(), oConfig.getDBPassword(), oConfig.getDBName());
    tabAreas = oConfig.getTabAreas();
    tabModules = oConfig.getTabModules(); 
    tabSymbols = oConfig.getTabSymbols();
    
    binitialized = true;
}

void BoneBase::tune(int direction, std::string areaName)
 {
    // sets the table that will be read or written
    if (direction == eTAB_CONTROL)
        this->tabMessages = oConfig.getTabControls();
    else if (direction == eTAB_SENSE)
        this->tabMessages = oConfig.getTabSenses();
    else
    {
        btuned = false;
        return;
    }
    
    // checks if the specified area name exist in the list of valid areas
    tunedArea = searchAreaByName(areaName);
    
    if (tunedArea > 0)
        btuned = true;   
};

void BoneBase::close()
{
    if (oDBClient.isConnected())
        oDBClient.disconnect();
}

std::vector<BoneArea> BoneBase::readAreas()
{    
    std::vector<BoneArea> listAreas;   

    // connect to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // perform query
    std::string select_areas = "SELECT * FROM " + tabAreas;
    sql::ResultSet* res = oDBClient.read(select_areas);
    
    // store obtained areas
    while (res->next())
    {        
       BoneArea oBoneArea(res->getInt("area"), res->getString("name"));
       listAreas.push_back(oBoneArea);
    }
    
    return listAreas;
}

std::vector<BoneModul> BoneBase::readAreaModules()
{    
    std::vector<BoneModul> listModules; 

    // connect to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // perform query
    std::string select_modules = "SELECT * FROM " + tabModules + 
                 + " where area = " + std::to_string(tunedArea);
    sql::ResultSet* res = oDBClient.read(select_modules);
    
    // store obtained modules
    while (res->next())
    {        
       BoneModul oBoneModul(res->getInt("area"), res->getInt("module"), res->getString("symbol"));
       listModules.push_back(oBoneModul);
    }
    
    return listModules;
}


std::vector<BoneSymbol> BoneBase::readAreaControls()
{    
    return readAreaSymbols(BoneSymbol::eCAT_CONTROL);
}


std::vector<BoneSymbol> BoneBase::readAreaSensors()
{    
    return readAreaSymbols(BoneSymbol::eCAT_SENSE);
}


std::vector<BoneSymbol> BoneBase::readAreaSymbols(int category)
{    
    std::vector<BoneSymbol> listSymbols; 

    // connect to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // perform query
    std::string select = "SELECT * FROM " + tabSymbols + 
                 + " where area = " + std::to_string(tunedArea) + 
                 + " and category = " + std::to_string(category);
    sql::ResultSet* res = oDBClient.read(select);
    
    // store obtained modules
    while (res->next())
    {        
       BoneSymbol oBoneSymbol(res->getInt("ID"), res->getInt("area"), res->getInt("category"), res->getString("symbol"), res->getString("name"));
       listSymbols.push_back(oBoneSymbol);
    }
    
    return listSymbols;
}


int BoneBase::searchAreaByName(std::string name)
{
    // connect to DB
    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    // perform query
    std::string select_area = "SELECT * FROM " + tabAreas +
                     + " where name = " + name;

    sql::ResultSet* res = oDBClient.read(select_area);
    
    // store obtained areas
    if (res->next())
       return res->getInt("area");
    else     
        return 0;
}

}