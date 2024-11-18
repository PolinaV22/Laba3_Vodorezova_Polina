#include "Compressor_St.h"
#include <iostream>

void Compressor_St::setName(std::string& n) {
    name = n;
}
void Compressor_St::setWorkshops(int& w) {
    workshopCount = w;
}
void Compressor_St::setActiveWorkshops(int& aw) {
    workshopsInOperation = aw;
}
void Compressor_St::setefficiency(int& ef) {
    efficiency = ef;
}
void Compressor_St::setdiametrentrance(int& dmt) {
    diametr = dmt;
}
void Compressor_St::setdiametrexit(int& dmex) {
    diametrexit = dmex;
}
std::string Compressor_St::getName() {
    return name;
}
int Compressor_St::getWorkshops() {
    return workshopCount;
}
int Compressor_St::getActiveWorkshops() {
    return workshopsInOperation;
}
int Compressor_St::getefficiency() {
    return efficiency;
}
int Compressor_St::getdiametrentrance() {
    return diametr;
}
int Compressor_St::getdiametrexit() {
    return diametrexit;
}

// Function for changing the state of the workshop
void Compressor_St::toggleWorkshopStatus() {
    int choice;
    int number;
    if (name == "." || workshopCount <= 0 || workshopsInOperation <= 0 || efficiency <= 0) {
        std::cout << "There is no compressor station. Perhaps you entered the data incorrectly or did not make it. Try again." << std::endl;
    }
    else {
        std::cout << "1. launch new workshops" << std::endl;
        std::cout << "2. Stop the workshops" << std::endl;
        std::cin >> choice;
        std::cout << "Enter how many workstations you want stop or launch." << std::endl;
        std::cin >> number;
        switch (choice) {
        case 1:
            if (workshopsInOperation < workshopCount && workshopsInOperation + number < workshopCount) {
                workshopsInOperation = workshopsInOperation + number;
                efficiency = (100 * workshopsInOperation) / workshopCount;
                std::cout << "Launched new workshop(s). Now in operation " << workshopsInOperation << " workshop(s)." << std::endl;
            }
            else {
                if (workshopsInOperation == workshopCount) {
                    std::cout << "All workshops are already running." << std::endl;
                }
                else {
                    std::cout << "The workflow cannot be executed because you want to enable more workstations than those that are not activated." << std::endl;
                }
            }
            break;
        case 2:
            if (workshopsInOperation > 0 && workshopsInOperation - number > 0) {
                workshopsInOperation = workshopsInOperation - number;
                efficiency = (100 * workshopsInOperation) / workshopCount;
                std::cout << "Some workshops were stopped. Now " << workshopsInOperation << " workshop(s) are in operation." << std::endl;
            }
            else {
                if (workshopsInOperation == 0) {
                    std::cout << "All workshops are already installed." << std::endl;
                }
                else {
                    std::cout << "The workflow cannot be completed because you want to disable more workstations than are activated." << std::endl;
                }
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
    }
}