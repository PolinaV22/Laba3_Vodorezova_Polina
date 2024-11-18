#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <vector>
#include <fstream>

class Cpipes
{
private:
    std::string name = { "." };
    int length = { 0 };
    int diameter = { 0 };
    bool isUnderRepair = { 0 };
    int entrance_st = { 0 };
    int exit_st = { 0 };
public:
    void setName(std::string& n);
    void setLength(int& l);
    void setDiameter(int& d);
    void setentrance(int& ent);
    void setexit(int& ex);
    std::string getName();
    int getLength();
    int getDiameter();
    bool getRepairStatus();
    void editRepairStatus();
    int getentranse_st();
    int getexite_st();
};
