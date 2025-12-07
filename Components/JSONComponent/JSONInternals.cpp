#include "JSONInternals.h"
#include "APIStruct.h"
#include "../../externals/json.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using ifstream = std::ifstream;

std::vector<APIStruct> JSONParser::ParseJson(const std::string& filePath) {
    std::vector<APIStruct> APIList;
    std::ifstream JSONFile(filePath);
    if (!JSONFile.is_open()) {
        std::cout << "JSON FILE NOT FOUND!" << std::endl;
        return {};
    }

    json j;
    JSONFile >> j;

    for (auto& k : j) {
        APIStruct api;
        api.name = k["name"].get<std::string>();
        api.rename = k["rename"].get<std::string>();
        api.returnType = k["ReturnType"].get<std::string>();

        api.parameters.clear();
        for (auto& p : k["Parameters"]) {
            api.parameters.push_back(p.get<std::string>());
        }

        api.ModuleName = k["ModuleName"].get<std::string>();
        api.hash = k["Hash"].get<uint32_t>();

        APIList.push_back(api);
    }

    return APIList;
}

bool JSONVerifier::VerifyStruct(const std::string& filePath) {
    std::ifstream JSONFile(filePath);
    if (!JSONFile.is_open()) return false;

    json j;
    try {
        JSONFile >> j;
    }
    catch (...) {
        return false;
    }

    for (const auto& k : j) {
        if (!k.contains("name") || !k["name"].is_string()) return false;
        if (!k.contains("rename") || !k["rename"].is_string()) return false;
        if (!k.contains("ReturnType") || !k["ReturnType"].is_string()) return false;
        if (!k.contains("Parameters") || !k["Parameters"].is_array()) return false;
        if (!k.contains("ModuleName") || !k["ModuleName"].is_string()) return false;
        if (!k.contains("Hash") || !k["Hash"].is_number_unsigned()) return false;
    }

    return true;
}
