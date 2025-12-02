#include "JSONInternals.h"
#include "externals/json.hpp"
#include <string>
#include <vector>
#include <fstream>

using json = nlohmann::json;
using ifstream = std::ifstream;

std::vector<APIStruct> JSONParser::ParseJson(const std::string& filePath) {
	std::vector <APIStruct> APIList;
	std::ifstream JSONFile(filePath);
	if (!JSONFile.is_open()) {
		return {}; 
	}
	json j;
	JSONFile >> j;

	for (auto& k : j) {
		APIStruct api;
		api.name = (std::string)k["name"];
		api.rename = (std::string)k["rename"];
		api.returnType = (std::string)k["ReturnType"];

		for (auto& p : k["Parameters"]) {
			api.parameters.push_back((std::string)p);
		}
		APIList.push_back(api);
	}
	return APIList;
}

