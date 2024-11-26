#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Cpipes.h"
#include "Compressor_St.h"
#include "functions.h"
#include <queue>

using namespace std;

void saveToFilepipes(map<int, Cpipes>& pipes, string& filename) {
    ofstream file(filename);
    functions f;
    if (file.is_open()) {
        for (auto& p : pipes) {
            file << "Pipe: " << p.first << "; Name: " << p.second.getName() << "; Length: " << p.second.getLength() << "; Diameter: " << p.second.getDiameter() << "; Under repair: " << p.second.getRepairStatus() << "; ID entrance compressor station: " << p.second.getentranse_st() << "; ID exit compressor station: " << p.second.getexite_st() << endl;
        }
        f.logAction("Saved to file: " + filename);
    }
    else {
        cerr << "Unable to open file for  saving" << endl;
        f.logAction("Not saved to file: " + filename);
    }
    file.close();
}
void saveToFilest(map<int, Compressor_St>& stations, string& filename) {
    ofstream file(filename, ios::app);
    functions f;
    if (file.is_open()) {
        for (auto& st : stations) {
            file << "Compressor_Station: " << st.first << "; Namest: " << st.second.getName() << "; Workshops: " << st.second.getWorkshops() << "; ActiveWorkshops: " << st.second.getActiveWorkshops() << "; Efficiency: " << st.second.getefficiency() << "; ID diameter entrance: " << st.second.getdiametrentrance() << "; ID diameter exit: " << st.second.getdiametrexit() << endl;
        }
        f.logAction("Saved to file: " + filename);
    }
    else {
        cerr << "Unable to open file for  saving" << endl;
        f.logAction("Not saved to file: " + filename);
    }
    file.close();
}

void loadFromFile(map<int, Cpipes>& pipes, map<int, Compressor_St>& stations, string& filename) {
    ifstream file(filename);
    Cpipes p;
    Compressor_St st;
    functions f;
    string name;
    int length;
    int diameter;
    int workshops;
    int activew;
    int efficiency;
    int status;
    int entrance;
    int exit;
    int entrancediameter;
    int exitdiameter;
    if (file.is_open()) {
        while (!file.eof()) {
            string line;
            while (getline(file, line)) {
                if (line.substr(0, 4) == "Pipe") {
                    size_t pos1 = line.find(';');
                    size_t pos2 = line.find(';', pos1 + 1);
                    size_t pos3 = line.find(';', pos2 + 1);
                    size_t pos4 = line.find(';', pos3 + 1);
                    size_t pos5 = line.find(';', pos4 + 1);
                    size_t pos6 = line.find(';', pos5 + 1);
                    name = line.substr(pos1 + 8, pos2 - pos1 - 8);
                    length = stoi(line.substr(pos2 + 10, pos3 - pos2 - 10));
                    diameter = stoi(line.substr(pos3 + 12, pos4 - pos3 - 12));
                    status = stoi(line.substr(pos4 + 16, pos5 - pos4 - 16));
                    entrance = stoi(line.substr(pos5 + 34, pos6 - pos5 - 34));
                    exit = stoi(line.substr(pos6 + 30, line.length() - pos6 - 30));
                    p.setName(name);
                    p.setLength(length);
                    p.setDiameter(diameter);
                    p.setentrance(entrance);
                    p.setexit(exit);
                    pipes.emplace(stoi(line.substr(6, pos1 - 6)), p);
                }
                else {
                    if (line.substr(0, 18) == "Compressor_Station") {
                        size_t pos1 = line.find(';');
                        size_t pos2 = line.find(';', pos1 + 1);
                        size_t pos3 = line.find(';', pos2 + 1);
                        size_t pos4 = line.find(';', pos3 + 1);
                        size_t pos5 = line.find(';', pos4 + 1);
                        size_t pos6 = line.find(';', pos5 + 1);
                        name = line.substr(pos1 + 10, pos2 - pos1 - 10);
                        workshops = stoi(line.substr(pos2 + 13, pos3 - pos2 - 13));
                        activew = stoi(line.substr(pos3 + 19, pos4 - pos3 - 19));
                        efficiency = stoi(line.substr(pos4 + 14, pos5 - pos4 - 14));
                        entrancediameter = stoi(line.substr(pos5 + 24, pos6 - pos5 - 24));
                        exitdiameter = stoi(line.substr(pos6 + 20, line.length() - pos6 - 20));
                        st.setName(name);
                        st.setWorkshops(workshops);
                        st.setActiveWorkshops(activew);
                        st.setefficiency(efficiency);
                        st.setdiametrentrance(entrancediameter);
                        st.setdiametrexit(exitdiameter);
                        stations.emplace(stoi(line.substr(20, pos1 - 20)), st);
                    }
                    else {
                        cerr << "Error reading line from file." << endl;
                        f.logAction("Error reading line from file: " + filename);
                    }
                }
            }
        }
        f.logAction("Loaded from file: " + filename);
    }
    else {
        cerr << "Could not open file." << endl;
        f.logAction("Could not open file: " + filename);
    }
    file.close();
}



// Main function
int main() {
    map<int, Cpipes> pipes;
    map<int, Compressor_St> stations;
    functions f;
    int choice; // Variable for selecting an action

    while (true) {
        cout << "---------------------------------------------------------" << endl;
        cout << "Menu: " << endl;
        cout << "1. Add Pipe" << endl;
        cout << "2. Add Compressor Station" << endl;
        cout << "3. Delite Pipe" << endl;
        cout << "4. Delite Compressor Station" << endl;
        cout << "5. View all objects" << endl;
        cout << "6. Edit Pipe" << endl;
        cout << "7. Edit Compressor Station" << endl;
        cout << "8. Search Pipes" << endl;
        cout << "9. Search Stations" << endl;
        cout << "10. Save to file" << endl;
        cout << "11. Load from file" << endl;
        cout << "12. Connection of pipes and compressor stations" << endl;
        cout << "13. Output the adjacency matrix" << endl;
        cout << "14. Topological sorting" << endl;
        cout << "0. Exit" << endl;
        cout << "---------------------------------------------------------" << endl;
        cin >> choice;
        cout << "---------------------------------------------------------" << endl;
        if (cin.fail() || choice < 0 || choice > 14 || cin.peek() != '\n') {
            cout << "Invalid input. Please enter an integer. " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1: {
            f.readPipe(pipes); // Reading data
            break;
        }
        case 2: {
            f.readst(stations); // Reading data
            break;
        }
        case 3: {
            f.delitepipes(pipes); // Reading data
            break;
        }
        case 4: {
            f.delitest(stations, pipes); // Reading data
            break;
        }
        case 5: {
            f.displayAllPipes(pipes); // Output data
            f.displayAllStations(stations); // Output data
            break;
        }
        case 6: {
            f.editPipe(pipes); // Editing status
            break;
        }
        case 7: {
            f.editStation(stations); // Change of workshop state
            break;
        }
        case 8: {
            f.searchPipes(pipes);
            break;
        }
        case 9: {
            f.searchStations(stations, pipes);
            break;
        }
        case 10: {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            saveToFilepipes(pipes, filename);
            saveToFilest(stations, filename);
            break;
        }
        case 11: {
            string filename;
            cout << "Enter filename to load: ";
            cin >> filename;
            loadFromFile(pipes, stations, filename);
            break;
        }
        case 12: {
            f.GPS(pipes, stations);
            break;
        }
        case 13: {
            f.matrix(pipes, stations);
            break;
        }
        case 14: {
            f.Topologicalsort(pipes, stations);
            break;
        }
        case 0:
            return 0;
        default: {
            cout << "Invalid choice!. Try again." << endl; // Incorrect choice
        }
               return 0;
        }
    }
}