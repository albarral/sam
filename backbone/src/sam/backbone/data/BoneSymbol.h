#ifndef __SAM_BACKBONE_BONESYMBOL_H
#define __SAM_BACKBONE_BONESYMBOL_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace sam 
{
class BoneSymbol
{
public:
    enum eCat
    {
        eCAT_NONE,                 // no category
        eCAT_SENSE,                // sense symbol
        eCAT_CONTROL             // control symbol
    };

private:
    int ID;                         // symbol ID
    int area;                     // area ID
    int category;               // category
    std::string symbol;     // symbol code  (MOVPOS, MOVNEG, BRAKE, START, STOP ... ) 
    std::string name;       // description of what the symbol means

public:    
    BoneSymbol(int ID, int area, int category, std::string symbol, std::string name);
    ~BoneSymbol();

    int getID() {return ID;};
    int getArea() {return area;};
    int getCategory() {return category;};
    std::string getSymbol() {return symbol;};
    std::string getName() {return name;};
};
}
#endif
