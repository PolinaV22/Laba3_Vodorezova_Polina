#include "functions.h"
#include <iostream>
#include <map>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <string>
#include <vector>
#include <fstream>

void functions::logAction(const std::string& action) {
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << action << " - " << std::endl;
    }
    else {
        std::cerr << "The log file could not be opened." << std::endl;
    }
    logFile.close();
}
void functions::readPipe(std::map<int, Cpipes>& pipes) {
    Cpipes p;
    std::string name;
    int length;
    int diameter;
    std::cout << "Enter pipe name (km mark): ";
    std::cin >> std::ws;
    getline(std::cin, name);
    p.setName(name);

    while (true) {
        std::cout << "Enter length (in km): ";
        std::cin >> length;
        if (std::cin.good() && length > 0 && std::cin.peek() == '\n') {
            p.setLength(length);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << std::endl;
        }
    }
    while (true) {
        std::cout << "Enter diameter in mm (500, 700, 1000 or 1400): ";
        std::cin >> diameter;
        if (std::cin.good() && diameter > 0 && (diameter == 500 || diameter == 700 || diameter == 1000 || diameter == 1400) && std::cin.peek() == '\n') {
            p.setDiameter(diameter);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << std::endl;
        }
    }
    int id = pipes.empty() ? 1 : (pipes.rbegin()->first + 1);
    pipes.emplace(id, p);
    logAction("Added pipe with ID " + std::to_string(id));
}


// Function to output pipe data
void functions::display(Cpipes& p) const {
    if (p.getName() == "." || p.getLength() <= 0 || p.getDiameter() <= 0) {
        std::cout << "There is no pipe. Perhaps you entered the pipe data incorrectly or did not add it. Try again." << std::endl;
    }
    else {
        std::cout << "Pipe: " << p.getName() << ", Length: " << p.getLength() << ", Diameter: " << p.getDiameter() << ", Under repair: " << (p.getRepairStatus() ? "Yes" : "No") << ", ID entrance compressor station: " << p.getentranse_st() << ", ID exit compressor station: " << p.getexite_st() << std::endl;
    }
}

void functions::displayAllPipes(std::map<int, Cpipes>& pipes) {
    if (size(pipes) == 0) {
        std::cout << "Pipes are not found." << std::endl;
    }
    else {
        for (auto& p : pipes) {
            std::cout << "ID: " << p.first << std::endl;
            display(p.second);
        }
    }
}

void functions::proverka_delite(int id, std::map<int, Cpipes>& pipes) {
    int init_value = {0};
    int choice;
    if (pipes[id].getentranse_st() == 0 && pipes[id].getexite_st() == 0) {
        pipes.erase(id);
        logAction("Delited pipe with ID " + std::to_string(id));
        std::cout << "The pipe was removed." << std::endl;
    }
    else {
        std::cout << "This pipe is used in the gas transportation network. Are you sure you want to remove it? (1 - yes, 2 - no)";
        std::cin >> choice;
        switch (choice) {
        case 1:
            pipes.erase(id);
            logAction("Delited pipe with ID " + std::to_string(id));
            std::cout << "The pipe was removed." << std::endl;
            break;
        case 2:
            std::cout << "The operation to remove the pipe from the gas transmission system was cancelled." << std::endl;
            logAction("The operation to remove the pipe from the gas transmission system was cancelled.");
            std::cout << "Switch the pipe to repair mode? (1 - yes, 2 - no)";
            std::cin >> choice;
            switch (choice) {
            case 1:
                pipes[id].editRepairStatus();
                logAction("Edited pipe with ID " + std::to_string(id));
                pipes[id].setentrance(init_value);
                pipes[id].setexit(init_value);
                logAction("The operation to change the state of the pipe was performed.");
                std::cout << "The operation to change the state of the pipe was performed." << std::endl;
                break;
            case 2:
                std::cout << "The operation to change the pipe's condition was cancelled." << std::endl;
                logAction("The operation to change the pipe's condition was cancelled.");
                break;
            default:
                std::cout << "The value entered is incorrect. Please, try again. " << std::endl;
                logAction("The value entered is incorrect.");
                break;
            }
            break;
        default:
            std::cout << "The value entered is incorrect. Please, try again. " << std::endl;
            logAction("The value entered is incorrect.");
            break;
        }
    }

}
void functions::delitepipes(std::map<int, Cpipes>& pipes) {
    int id;
    std::cout << "Enter the index of the pipe you want to delite:" << std::endl;
    std::cin >> id;
    if (pipes.find(id) != pipes.end()) {
        proverka_delite(id, pipes);
    }
    else {
        std::cout << "Pipe is not found." << std::endl;
    }
}

void functions::editPipe(std::map<int, Cpipes>& pipes) {
    int id;
    int init_value = { 0 };
    std::cout << "Enter pipe ID to edit: ";
    std::cin >> id;
    if (pipes.find(id) != pipes.end()) {
        pipes[id].editRepairStatus();
        logAction("Edited pipe with ID " + std::to_string(id));
        if (pipes[id].getRepairStatus() == 0) {
            pipes[id].setentrance(init_value);
            pipes[id].setexit(init_value);
        }
    }
    else {
        std::cout << "Pipe is not found." << std::endl;
    }
}


void functions::batchPipes(std::map<int, Cpipes>& pipes) {
    bool editAll;
    int init_value = { 0 };
    int choice;
    std::cout << "Edit all pipes? (1 for yes, 0 for no): ";
    std::cin >> editAll;
    std::cout << "1.Delite" << std::endl;
    std::cout << "2.Change" << std::endl;
    std::cin >> choice;
    if (editAll) {
        switch (choice) {
        case 1:
            if (size(pipes) == 0) {
                std::cout << "Pipes are not found" << std::endl;
                break;
            }
            for (auto& pipe : pipes) {
                proverka_delite(int(pipe.first), pipes);
            }
            logAction("Batch delited all pipes.");
            break;
        case 2:
            if (size(pipes) == 0) {
                std::cout << "Pipes are not found" << std::endl;
                break;
            }
            for (auto& pipe : pipes) {
                pipe.second.editRepairStatus();
                if (pipe.second.getRepairStatus() == 0) {
                    pipe.second.setentrance(init_value);
                    pipe.second.setexit(init_value);
                }
            }
            logAction("Batch edited all pipes.");
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
    }
    else {
        std::vector<int> ids;
        int id;
        std::cout << "Enter pipe IDs to edit or delite (enter -1 to stop): ";
        while (std::cin >> id && id != -1) {
            if (pipes.find(id) != pipes.end()) {
                ids.push_back(id);
            }
            else {
                std::cout << "Pipe with ID " << id << " not found." << std::endl;
            }
        }
        switch (choice) {
        case 1:
            for (int pipeId : ids) {
                proverka_delite(pipeId, pipes);
            }
            logAction("Batch delited selected pipes.");
            break;
        case 2:
            for (int pipeId : ids) {
                pipes[pipeId].editRepairStatus();
                if (pipes[pipeId].getRepairStatus() == 0) {
                    pipes[pipeId].setentrance(init_value);
                    pipes[pipeId].setexit(init_value);
                }
            }
            logAction("Batch edited selected pipes.");
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
    }
}

// Function for reading CS data
void functions::readst(std::map<int, Compressor_St>& stations) {
    Compressor_St st;
    std::string name;
    int workshopCount;
    int workshopsInOperation;
    int efficiency;
    int entrance;
    int exit;

    std::cout << "Enter compressor station name: ";
    std::cin >> std::ws;
    getline(std::cin, name);
    st.setName(name);

    while (true) {
        std::cout << "Enter number of workshops: ";
        std::cin >> workshopCount;
        if (std::cin.good() && workshopCount > 0 && std::cin.peek() == '\n') {
            st.setWorkshops(workshopCount);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive and greater than zero. " << std::endl;
        }
    }
    while (true) {
        std::cout << "Enter number of workshops in operation: ";
        std::cin >> workshopsInOperation;
        if (std::cin.good() && workshopsInOperation > 0 && workshopsInOperation <= workshopCount && std::cin.peek() == '\n') {
            st.setActiveWorkshops(workshopsInOperation);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive number greater than zero and less than the number of workstations. " << std::endl;
        }
    }
    while (true) {
        std::cout << "Enter compressor station inlet dimeter (500, 700, 1000 or 1400): ";
        std::cin >> entrance;
        if (std::cin.good() && (entrance == 500 || entrance == 700 || entrance == 1000 || entrance == 1400) && std::cin.peek() == '\n') {
            st.setdiametrentrance(entrance);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive number greater than zero. " << std::endl;
        }
    }
    while (true) {
        std::cout << "Enter compressor station outlet dimeter (500, 700, 1000 or 1400): ";
        std::cin >> exit;
        if (std::cin.good() && (exit == 500 || exit == 700 || exit == 1000 || exit == 1400) && std::cin.peek() == '\n') {
            st.setdiametrexit(exit);
            break;
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer that is positive number greater than zero. " << std::endl;
        }
    }
    if (workshopCount == 0) {
        efficiency = 0;
    }
    else {
        efficiency = (100 * workshopsInOperation) / workshopCount;
    }
    st.setefficiency(efficiency);
    int id = stations.empty() ? 1 : (stations.rbegin()->first + 1);
    stations.emplace(id, st);
    logAction("Added compressor station with ID " + std::to_string(id));
}
void functions::proverka_delitest(int id, std::map<int, Compressor_St>& stations, std::map<int, Cpipes>& pipes) {
    int id_st = {0};
    int init_value = { 0 };
    int choice;
    for (auto& p : pipes) {
        if (p.second.getentranse_st() == id || p.second.getexite_st() == id) {
            id_st = 1;
            break;
        }
    }
    if (id_st == 0) {
        stations.erase(id);
        logAction("Delited compressor station with ID " + std::to_string(id));
    }
    else {
        std::cout << "The compressor station is part of the gas transportation system. Are you sure you want to delete it? (1-yes, 2-no).";
        std::cin >> choice;
        switch (choice) {
        case 1:
            stations.erase(id);
            for (auto& p : pipes) {
                if (p.second.getentranse_st() == id || p.second.getexite_st() == id) {
                    p.second.setentrance(init_value);
                    p.second.setexit(init_value);
                    logAction("Pipe with ID disconnected " + std::to_string(p.first));
                }
            }
            logAction("Delited compressor station with ID " + std::to_string(id));
            std::cout << "The compressor sttion was removed." << std::endl;
            break;
        case 2:
            std::cout << "The operation to remove the compressor station from the gas transmission system was cancelled." << std::endl;
            logAction("The operation to remove the compressor station from the gas transmission system was cancelled.");
            break;
        default:
            std::cout << "The value entered is incorrect. Please, try again. " << std::endl;
            logAction("The value entered is incorrect.");
            break;
        }
    }
}
void functions::delitest(std::map<int, Compressor_St>& stations, std::map<int, Cpipes>& pipes) {
    int id;
    int id_st = { 0 };
    int choice;
    std::cout << "Enter the index of the Compressor station you want to delite:" << std::endl;
    std::cin >> id;
    if (stations.find(id) != stations.end()) {
        proverka_delitest(id, stations, pipes);
    }
    else {
        std::cout << "Station is not found." << std::endl;
    }
}


void functions::displayst(Compressor_St& st) const {
    if (st.getName() == "." || st.getWorkshops() <= 0 || st.getActiveWorkshops() <= 0 || st.getefficiency() <= 0) {
        std::cout << "There is no compressor station. Perhaps you entered the data incorrectly or did not make it. Try again." << std::endl;
    }
    else {
        std::cout << "Compressor Station: " << st.getName() << ", Workshops: " << st.getWorkshops() << ", In operation: " << st.getActiveWorkshops() << ", Efficiency: " << st.getefficiency() << ", ID diameter entrance: " << st.getdiametrentrance() << ", ID diameter exit: " << st.getdiametrexit() << std::endl;
    }
}

void functions::displayAllStations(std::map<int, Compressor_St>& stations) {
    if (size(stations) == 0) {
        std::cout << "Compressor stations are not found." << std::endl;
    }
    else {
        for (auto& cs : stations) {
            std::cout << "ID: " << cs.first << std::endl;
            displayst(cs.second);
        }
    }
}

void functions::editStation(std::map<int, Compressor_St>& stations) {
    int id;
    std::cout << "Enter station ID to edit: ";
    std::cin >> id;
    if (stations.find(id) != stations.end()) {
        stations[id].toggleWorkshopStatus();
        logAction("Edited compressor station with ID " + std::to_string(id));
    }
    else {
        std::cout << "Station is not found." << std::endl;
    }
}

void functions::searchPipes(std::map<int, Cpipes>& pipes) {
    std::string query;
    bool inRepair;
    int choice;
    int init_value = { 0 };
    std::vector<int> ids;
    std::cout << "1.Search by pipe name" << std::endl;
    std::cout << "2.Search by repair status" << std::endl;
    std::cout << "3.Batch Edit Pipes" << std::endl;
    std::cin >> choice;
    switch (choice) {
    case 1:
        std::cout << "Enter pipe name to search: ";
        std::cin >> std::ws;
        getline(std::cin, query);
        for (auto& p : pipes) {
            if (p.second.getName().find(query) != std::string::npos || p.second.getName().rfind(query) != std::string::npos) {
                std::cout << "ID: " << p.first << " ";
                display(p.second);
                ids.push_back(p.first);
            }
        }
        if (size(ids) == 0) {
            std::cout << "Pipes are not found" << std::endl;
            break;
        }
        std::cout << "1.Delite" << std::endl;
        std::cout << "2.Change" << std::endl;
        std::cin >> choice;
        switch (choice) {
        case 1:
            for (int idd : ids) {
                proverka_delite(idd, pipes);
                logAction("Delited pipe with ID " + std::to_string(idd));
            }
            break;
        case 2:
            for (int idd : ids) {
                pipes[idd].editRepairStatus();
                if (pipes[idd].getRepairStatus() == 0) {
                    pipes[idd].setentrance(init_value);
                    pipes[idd].setexit(init_value);
                }
                logAction("Edited pipe with ID " + std::to_string(idd));
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    case 2:
        std::cout << "Filter by repair status (1 for yes, 0 for no): ";
        std::cin >> inRepair;
        for (auto& p : pipes) {
            if (p.second.getRepairStatus() == inRepair) {
                std::cout << "ID: " << p.first << " ";
                display(p.second);
                ids.push_back(p.first);
            }
        }
        if (size(ids) == 0) {
            std::cout << "Pipes are not found" << std::endl;
            break;
        }
        std::cout << "1.Delite" << std::endl;
        std::cout << "2.Change" << std::endl;
        std::cin >> choice;
        switch (choice) {
        case 1:
            for (int idd : ids) {
                proverka_delite(idd, pipes);
                logAction("Delited pipe with ID " + std::to_string(idd));
            }
            break;
        case 2:
            for (int idd : ids) {
                pipes[idd].editRepairStatus();
                if (pipes[idd].getRepairStatus() == 0) {
                    pipes[idd].setentrance(init_value);
                    pipes[idd].setexit(init_value);
                }
                logAction("Edited pipe with ID " + std::to_string(idd));
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    case 3:
        batchPipes(pipes);
        break;

    default:
        std::cout << "Invalid choice! Try again." << std::endl;
        break;
    }
}
void functions::searchStations(std::map<int, Compressor_St>& stations, std::map<int, Cpipes>& pipes) {
    std::string query;
    std::vector<int> ids;
    double maxIdlePercentage;
    int choice;
    int percent;
    std::cout << "1.Search by compressor station name" << std::endl;
    std::cout << "2.Search by efficienty" << std::endl;
    std::cin >> choice;
    switch (choice) {
    case 1:
        std::cout << "Enter compressor station name to search: ";
        std::cin >> std::ws;
        getline(std::cin, query);
        for (auto& cs : stations) {
            if (cs.second.getName().find(query) != std::string::npos || cs.second.getName().rfind(query) != std::string::npos) {
                std::cout << "ID: " << cs.first << " ";
                displayst(cs.second);
                ids.push_back(cs.first);
            }
        }
        if (size(ids) == 0) {
            std::cout << "Compressor stations are not found." << std::endl;
            break;
        }
        std::cout << "1.Delite" << std::endl;
        std::cout << "2.Change" << std::endl;
        std::cin >> choice;
        switch (choice) {
        case 1:
            for (int idd : ids) {
                proverka_delitest(idd, stations, pipes);
                logAction("Delited station with ID " + std::to_string(idd));
            }
            break;
        case 2:
            for (int idd : ids) {
                stations[idd].toggleWorkshopStatus();
                logAction("Edited Compressor station with ID " + std::to_string(idd));
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    case 2:
        std::cout << "Enter maximum idle percentage: ";
        std::cin >> maxIdlePercentage;
        std::cout << "1. Output of compressor stations with a lower percentage of efficiency indicated." << std::endl;
        std::cout << "2. Output of compressor stations with a high percentage of efficiency indicated." << std::endl;
        std::cin >> percent;
        switch (percent) {
        case 1:
            for (auto& cs : stations) {
                if (100 - cs.second.getefficiency() <= maxIdlePercentage) {
                    std::cout << "ID: " << cs.first << " ";
                    displayst(cs.second);
                    ids.push_back(cs.first);
                }
            }
            if (size(ids) == 0) {
                std::cout << "Compressor stations are not found" << std::endl;
                break;
            }
            std::cout << "1.Delite" << std::endl;
            std::cout << "2.Change" << std::endl;
            std::cin >> choice;
            switch (choice) {
            case 1:
                for (int idd : ids) {
                    proverka_delitest(idd, stations, pipes);
                    logAction("Delited station with ID " + std::to_string(idd));
                }
                break;
            case 2:
                for (int idd : ids) {
                    stations[idd].toggleWorkshopStatus();
                    logAction("Edited Costation with ID " + std::to_string(idd));
                }
                break;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
                break;
            }
            break;
        case 2:
            for (auto& cs : stations) {
                if (100 - cs.second.getefficiency() >= maxIdlePercentage) {
                    std::cout << "ID: " << cs.first << " ";
                    displayst(cs.second);
                    ids.push_back(cs.first);
                }
            }
            if (size(ids) == 0) {
                std::cout << "Compressor stations are not found" << std::endl;
                break;
            }
            std::cout << "1.Delite" << std::endl;
            std::cout << "2.Change" << std::endl;
            std::cin >> choice;
            switch (choice) {
            case 1:
                for (int idd : ids) {
                    proverka_delitest(idd, stations, pipes);
                    logAction("Delited station with ID " + std::to_string(idd));
                }
                break;
            case 2:
                for (int idd : ids) {
                    stations[idd].toggleWorkshopStatus();
                    logAction("Edited Compressor station with ID " + std::to_string(idd));
                }
                break;
            default:
                std::cout << "Invalid choice! Try again." << std::endl;
                break;
            }
            break;
        default:
            std::cout << "Invalid choice! Try again." << std::endl;
            break;
        }
        break;
    default:
        std::cout << "Invalid choice! Try again." << std::endl;
        break;
    }
}
void functions::GPS(std::map<int, Cpipes>& pipes, std::map<int, Compressor_St>& stations) {
    int id;
    int idexit;
    int pipeid = { 0 };
    int choice;
    std::cout << "Enter ID of the compressor station you want to connect to the pipe inlet: ";
    std::cin >> id;
    std::cout << "Enter ID of the compressor station you want to connect to the pipe outlet: ";
    std::cin >> idexit;
    if (stations.find(id) != stations.end() && stations.find(idexit) !=stations.end() && id != idexit) {
        if (stations[id].getdiametrentrance() == stations[idexit].getdiametrexit()) {
            for (auto& p : pipes) {
                if (p.second.getDiameter() == stations[id].getdiametrentrance() && p.second.getentranse_st() == 0 && p.second.getexite_st() == 0 && p.second.getRepairStatus() == 1) {
                    p.second.setentrance(id);
                    p.second.setexit(idexit);
                    pipeid = int(p.first);
                    logAction("Compressor stations " + std::to_string(id) + " and " + std::to_string(idexit) + "were connected by a pipe to the id" + std::to_string(pipeid));
                    break;
                }
            }
            if (pipeid == 0) {
                std::cout << "Pipes of this diameter do not exist. Do you want to create a new one?" << std::endl;
                std::cout << "Enter 1 if answer is yes and 2 if the answer is no." << std::endl;
                std::cin >> choice;
                switch (choice) {
                case 1:
                    readPipe(pipes);
                    std::cout << "Do you still want to connect the selected compressor stations?" << std::endl;
                    std::cout << "Enter 1 if answer is yes and 2 if the answer is no." << std::endl;
                    std::cin >> choice;
                    switch(choice) {
                    case 1:
                        pipeid = pipes.rbegin()->first;
                        pipes[pipeid].editRepairStatus();
                        pipes[pipeid].setentrance(id);
                        pipes[pipeid].setexit(idexit);
                        logAction("Compressor stations " + std::to_string(id) + " and " + std::to_string(idexit) + "were connected by a pipe to the id" + std::to_string(pipeid));
                        break;
                    case 2:
                        logAction("The operation to connect compressor stations with a new pipe has been cancelled.");
                        break;
                    default:
                        std::cout << "The value entered is incorrect. Please, try again. " << std::endl;
                        logAction("The value entered is incorrect.");
                        break;
                    }
                    break;
                case 2:
                    logAction("The operation to create a new pipeline and connect it to the gas transportation network was cancelled.");
                    break;
                }

            }
        }
        else {
            std::cout << "The selected compressor stations are not suitable because the input and output of the selected compressor stations do not match." << std::endl;
            std::cout << "Do you want to see all the compressor stations and pipes that exist? (1 - Yes, 2 - No)" << std::endl;
            std::cin >> choice;
            switch(choice) {
            case 1:
                displayAllPipes(pipes);
                displayAllStations(stations);
                logAction("Output of all compressor stations and pipes.");
                break;
            case 2:
                std::cout << "Operation canceled." << std::endl;
                logAction("The operation to remove all pipes and compressor stations was cancelled.");
                break;
            default:
                std::cout << "The value entered is incorrect. Please, try again. " << std::endl;
                logAction("The value entered is incorrect.");
                break;
            }
        }
    }
    else {
        std::cout << "Station(s) are not found or you specified the id of the same station." << std::endl;
        logAction("Station(s) are not found or you specified the id of the same station.");
        std::cout << "Do you want to see all the compressor stations and pipes that exist? (1 - Yes, 2 - No)" << std::endl;
        std::cin >> choice;
        switch(choice) {
        case 1:
            displayAllPipes(pipes);
            displayAllStations(stations);
            logAction("Output of all compressor stations and pipes.");
            break;
        case 2:
            std::cout << "Operation canceled." << std::endl;
            logAction("The operation to remove all pipes and compressor stations was cancelled.");
            break;
        default:
            std::cout << "The value entered is incorrect. Please, try again. " << std::endl;
            logAction("The value entered is incorrect.");
            break;
        }
    }
}

void functions::matrix(std::map<int, Cpipes>& pipes, std::map<int, Compressor_St>& stations) {
    int i = { 0 };
    int j = { 0 };
    size_t numPipes = pipes.size();
    size_t numStations = stations.size();
    std::vector <std::vector <int> > matrix(numPipes, std::vector <int> (numStations, 0));
    for (auto& p : pipes) {
        j = 0;
        for (auto& st : stations) {
            if (p.second.getentranse_st() == st.first || p.second.getexite_st() == st.first) {
                matrix[i][j] = 1;
            }
            j = j + 1;
        }
        i = i + 1;
    }
}
