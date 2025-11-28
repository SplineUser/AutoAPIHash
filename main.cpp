#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <shlwapi.h>
#include <vector>
#include "externals/json.hpp"
#pragma comment(lib, "shlwapi.lib")
#define ERROR_CODE 1

using json = nlohmann::json;
using ifstream = std::ifstream;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Please enter the file location! Usage example: ITR c:\\users\\public\\desktop\\file.cpp");
		return ERROR_CODE;
	}
	char* filePath = argv[1];

	bool File_Exists = PathFileExistsA(filePath);
	if (!File_Exists) {
		printf("The file at location %s does not exist!", filePath);
		return ERROR_CODE;
	}

	ifstream JSONFile("api_list.json");
	json api_data = json::parse(JSONFile);



	// Reading file to find the API
	std::ifstream MyFile(filePath);
	std::string line;
	std::vector <std::string> body;
	while (std::getline(MyFile, line)) {
		for (size_t i = 0; i < api_data.size(); i++) {
			const auto& api_name = api_data[i]["name"];
			const auto& api_found = line.find(api_name);
			const auto& rename_str = api_data[i]["rename"];
			if (api_found != std::string::npos) {
				line.replace(api_found, api_name.size(), rename_str);
			}
		}
		body.push_back(line);
	}
	MyFile.close();
	// Writing back to the file
	std::ofstream MyFileOut(filePath);
	for (const auto& str : body) {
		MyFileOut << str << std::endl;
	}
	MyFile.close();


	
	Sleep(2000);
	return 0;
}