#include "SourceInternals.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using ifstream = std::ifstream;
using ofstream = std::ofstream;

void SourceTransform::setFilePath(std::string filePath){
	PerfilePath = filePath;
}

bool SourceTransform::LoadFile(){
	ifstream SourceFile(PerfilePath);
	if (!SourceFile.is_open()) {
		std::cout << "Error opening the source file" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(SourceFile, line)){
		code_lines.push_back(line);
	}
	SourceFile.close();
	return true;
}

bool SourceTransform::ReplaceText(const std::vector<std::pair<std::string, std::string>>& APIList) {
	bool changed = false;

	for (const auto& api : APIList) {        
		for (auto& line : code_lines) {          
			size_t pos = 0;
			while ((pos = line.find(api.first, pos)) != std::string::npos) {
				line.replace(pos, api.first.length(), api.second);
				pos += api.second.length();     
				changed = true;
			}
		}
	}

	return changed;  
}

bool SourceTransform::SaveFile(){
	std::ofstream file(PerfilePath); 
	if (!file.is_open()) {
		std::cerr << "Failed to open file for writing: " << PerfilePath << std::endl;
		return false;
	}

	for (const auto& line : code_lines) {
		file << line << "\n";  
	}

	file.close(); 
	return true;
}