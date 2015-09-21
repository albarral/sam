/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include "BoneConnection.h"

namespace sam 
{  
namespace backbone 
{
BoneConnection::BoneConnection() 
{
    binitialized = false;
}

void BoneConnection::init()
{
    // sets database connection params
    oDBClient.setURL(oConfig.getDBServerUrl());
    oDBClient.init(oConfig.getDBName(), oConfig.getDBUser(), oConfig.getDBPassword());    
    binitialized = true;
}

void BoneConnection::close()
{
    if (oDBClient.isConnected())
        oDBClient.disconnect();
}


//std::vector<BoneSymbol> BoneConnection::readAreaSymbols(int category)
//{    
//    std::vector<BoneSymbol> listSymbols; 
//
//    // connect to DB
//    if (!oDBClient.isConnected())
//        oDBClient.connect();
//    
//    // perform query
//    std::string select = "SELECT * FROM " + tabSymbols + 
//                 + " where (area = " + std::to_string(areaGeneralSymbol) + " or area = " + std::to_string(tunedArea) + " ) "
//                 + " and category = " + std::to_string(category);
//    sql::ResultSet* res = oDBClient.read(select);
//    
//    // store obtained modules
//    while (res->next())
//    {        
//       BoneSymbol oBoneSymbol(res->getInt("ID"), res->getInt("area"), res->getInt("category"), res->getString("symbol"), res->getString("name"));
//       listSymbols.push_back(oBoneSymbol);
//    }
//    
//    return listSymbols;
//}


}
}