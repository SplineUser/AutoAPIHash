#include "Components/JSONComponent/JSONConfigManager.cpp"
#include "Components/JSONComponent/APIStruct.h"
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string filePath = "C:\\Users\\Priyan\\source\\repos\\Import_Table_Reducer\\x64\\Debug\\api_list.json";
    std::string apiName = "VirtualAlloc";

    JSONConfigManager mJCM;

    bool loaded = mJCM.LoadConfig(filePath);
    std::cout << "Loaded: " << loaded << std::endl;

    auto APIList = mJCM.getAPIList();
    std::cout << "API List:\n";
    for (const auto& name : APIList) {
        std::cout << " - " << name << std::endl;
    }

    APIStruct Tempapi = mJCM.getAPIStruct(apiName);
    std::cout << "\nAPI Struct for " << Tempapi.name << ":\n";
    std::cout << "Rename: " << Tempapi.rename << "\n";
    std::cout << "Return Type: " << Tempapi.returnType << "\n";
    std::cout << "Parameters:\n";
    for (const auto& param : Tempapi.parameters) {
        std::cout << " * " << param << "\n";
    }

    return 0;
}