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
    tabAreas = "TAB_AREAS";
    tabModules = "TAB_MODULES";
}

void BoneBase::init(std::string url, std::string user, std::string password, std::string schema)
{
    oDBClient.init(url, user, password, schema);
    
    readAreas();
    readModules();
    binitialized = true;
}

void BoneBase::tune(std::string tabMessages, std::string area)
 {
    this->tabMessages = tabMessages;
    myAreaID = searchAreaID(area);
    
    if (myAreaID > 0)
        btuned = true;   
};

void BoneBase::close()
{
    if (oDBClient.isConnected())
        oDBClient.disconnect();
}

void BoneBase::readAreas()
{    
    listAreas.clear();    

    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    std::string select_areas = "SELECT * FROM " + tabAreas;
    sql::ResultSet* res = oDBClient.read(select_areas);
    
    while (res->next())
    {        
       BoneArea oBoneArea(res->getInt("ID"), res->getString("area"));
       listAreas.push_back(oBoneArea);
    }
}

void BoneBase::readModules()
{    
    listModules.clear();    

    if (!oDBClient.isConnected())
        oDBClient.connect();
    
    std::string select_modules = "SELECT * FROM " + tabModules;
    sql::ResultSet* res = oDBClient.read(select_modules);
    
    while (res->next())
    {        
       BoneModul oBoneModul(res->getInt("areaID"), res->getInt("moduleID"), res->getString("modul"));
       listModules.push_back(oBoneModul);
    }
}

int BoneBase::searchAreaID(std::string area)
{
    int ID = 0;
    std::vector<BoneArea>::iterator it_area = listAreas.begin();
    
    while (it_area != listAreas.end())
    {
        // compares given area with list of areas 
        if (area.compare(it_area->getArea()) == 0)
        {
            ID = it_area->getID();
            break;            
        }           
        it_area++;
    }
    
    return ID;
}

int BoneBase::searchModuleID(int areaID, std::string module)
{
    int ID = 0;
    std::vector<BoneModul>::iterator it_module = listModules.begin();
    
    while (it_module != listModules.end())
    {
        // compares given area with list of areas 
        if ( (areaID == it_module->getAreaID()) && 
             (module.compare(it_module->getModule()) == 0) )
        {
            ID = it_module->getModuleID();
            break;            
        }           
        it_module++;
    }
    
    return ID;
}
}