/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

// TEST: SAM MANIPULATION

#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "sam/manipulation/ArmManager.h"
#include "sam/backbone/utils/DatabaseClient.h"  // for test
#include "sam/backbone/data/BoneMsg.h"


void testManipulation();
void testBackbone();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("sam.manipulation"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    //testManipulation();
    testBackbone();
      
    return 0;
}

void testManipulation()
{
    LOG4CXX_INFO(logger, "<<<<<<<<<<<<<<<< TEST MANIPULATION >>>>>>>>>>>>>>");      
    
    std::vector<float> listPrevAngles;
    
    sam::ArmManager oArmManager; 
    oArmManager.init("UR5");
    if (!oArmManager.isEnabled())
        return;
    
    oArmManager.startModules();
    
    while (!oArmManager.checkEndRequested()) 
    {
        oArmManager.readSollAngles();
        std::vector<float>& listSollAngles = oArmManager.getSollAngles();
        
        if (listSollAngles != listPrevAngles)
        {
            LOG4CXX_INFO(logger,"moved angles: " << (int)listSollAngles.at(0) << ", " << (int)listSollAngles.at(1) << ", " << (int)listSollAngles.at(2) << ", " << (int)listSollAngles.at(3));      
            listPrevAngles = listSollAngles;            
        }

        sleep(1);
    }    
    
    oArmManager.stopModules();

    return;
}

void testBackbone()
{
    LOG4CXX_INFO(logger, "<<<<<<<<<<<<<<<< TEST BACKBONE >>>>>>>>>>>>>>");      

   std::string  j1_right = "update TAB_CONTROL set info=3, proc=0 where area=1 and module=9";
   std::string  j1_brake = "update TAB_CONTROL set info=5, proc=0 where area=1 and module=9";
   std::string  j1_stop = "update TAB_CONTROL set info=2, proc=0 where area=1 and module=9";

  std::string select = "SELECT * FROM TAB_CONTROL where area = 1 and proc = 0";
    
    // partial query (module needs to be informed)
   std::string  updateOK = "update TAB_CONTROL set proc=1 where area=1 and module=9";
    
    sam::DatabaseClient oDBClient;          // handler for database connections
    oDBClient.init("tcp://127.0.0.1:3306", "sam", "sam", "SAM_BACKBONE");    
    oDBClient.connect();

    if (!oDBClient.isConnected())
        LOG4CXX_INFO(logger, "connection failed");        
    
    oDBClient.write(j1_right);
  
    int counter = 0;
    
    while (counter < 5)
    {
        LOG4CXX_INFO(logger, "iter " << counter);
        // fetches new messages from DB & builds the unprocessed messages list    
        sql::ResultSet* res = oDBClient.read(select);    
        while (res->next())
        {        
           sam::BoneMsg oBoneMsg(res->getInt("area"), res->getInt("module"), res->getInt("info"), res->getInt("detail"));
           LOG4CXX_INFO(logger, "message : " << oBoneMsg.toString());
        }
                
        counter++;
        if (counter==3)
            oDBClient.write(j1_brake);
    }

    LOG4CXX_INFO(logger, "TEST FINISHED");      
}