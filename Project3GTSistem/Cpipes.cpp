#include "Cpipes.h"
#include <iostream>


void Cpipes::setName(std::string& n) {
    name = n;
}
void Cpipes::setLength(int& l) {
    length = l;
}
void Cpipes::setDiameter(int& d) {
    diameter = d;
}
void Cpipes::setentrance(int& ent) {
    entrance_st = ent;
}
void Cpipes::setexit(int& ex) {
    exit_st = ex;
}
std::string Cpipes::getName() {
    return name;
}
int Cpipes::getLength() {
    return length;
}
int Cpipes::getDiameter() {
    return diameter;
}
bool Cpipes::getRepairStatus() {
    return isUnderRepair;
}
int Cpipes::getentranse_st() {
    return  entrance_st;
}
int Cpipes::getexite_st() {
    return  exit_st;
}

// Function for editing the "under repair" state
void Cpipes::editRepairStatus() {
    if (name == "." || length <= 0 || diameter <= 0) {
        std::cout << "There is no pipe, so this option does not work. Please enter the pipe details." << std::endl;
    }
    else {
        isUnderRepair = !isUnderRepair;// Changes the state to the opposite
        std::cout << "workshop condition" << std::endl;
        std::cout << (isUnderRepair ? "Yes" : "No") << std::endl;
    }
}