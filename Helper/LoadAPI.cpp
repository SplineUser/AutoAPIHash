#include "LoadAPI.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

bool LoadAPI::APILoad(const std::string& configPath, std::string& API_value) {
	std::ifstream configFile(configPath);
	if (!configFile.is_open()) {
		API_value = "";
		return false;
	}
	std::string line;
	getline(configFile, line);

	API_value = line;
	return true;

}