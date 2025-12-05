#include "SourceInternals.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using ifstream = std::ifstream;

void SourceTransform::setFilePath(std::string filePath){
	PerfilePath = filePath;
}

bool SourceTransform::LoadFile(){
	ifstream SourceFile(filePath);
	if (!SourceFile.is_open) {
		std::cout << "Error opening source file" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(SourceFile, line)){
		code_lines.push_back(line);
	}
	SourceFile.close()
	return true;
}

bool SourceTransform::ReplaceText(std::vector<std::pair<std::string, std::string>> APIList){

}

bool SourceTransform::SaveFile(std::string filePath){}