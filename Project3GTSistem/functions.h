#pragma once
#include <string>
#include <map>
#include <iostream>
#include "Cpipes.h"
#include "Compressor_St.h"
#include <vector>
#include <fstream>
#include <queue>

class functions
{
public:
	void logAction(const std::string& action);
	void readPipe(std::map<int, Cpipes>& pipes);
	void display(Cpipes& p) const;
	//friend std::ostream& operator<<(std::ostream& out, Cpipes& p);
	void displayAllPipes(std::map<int, Cpipes>& pipes);
	void proverka_delite(int id, std::map<int, Cpipes>& pipes);
	void delitepipes(std::map<int, Cpipes>& pipes);
	void editPipe(std::map<int, Cpipes>& pipes);
	void batchPipes(std::map<int, Cpipes>& pipes);
	void readst(std::map<int, Compressor_St>& stations);
	void proverka_delitest(int id, std::map<int, Compressor_St>& stations, std::map<int, Cpipes>& pipes);
	void delitest(std::map<int, Compressor_St>& stations, std::map<int, Cpipes>& pipes);
	void displayst(Compressor_St& st) const;
	void displayAllStations(std::map<int, Compressor_St>& stations);
	void editStation(std::map<int, Compressor_St>& stations);
	void searchPipes(std::map<int, Cpipes>& pipes);
	void searchStations(std::map<int, Compressor_St>& stations, std::map<int, Cpipes>& pipes);
	void GPS(std::map<int, Cpipes>& pipes, std::map<int, Compressor_St>& stations);
	void matrix(std::map<int, Cpipes>& pipes, std::map<int, Compressor_St>& stations);
	std::vector<std::vector<bool>> incidenceToAdjacency(const std::vector<std::vector<int>>& incidenceMatrix);
	bool hasCycle(const std::vector<std::vector<bool>>& adjMatrix, int node, std::vector<bool>& visited, std::vector<bool>& recursionStack);
	bool isCyclic(const std::vector<std::vector<bool>>& adjMatrix);
	int findRoot(const std::vector<std::vector<bool>>& adjMatrix);
	std::vector<int> topologicalSort(const std::vector<std::vector<bool>>& adjMatrix);
	void Topologicalsort(std::map<int, Cpipes>& pipes, std::map<int, Compressor_St>& stations);
};

