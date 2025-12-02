#pragma once
#include <string>
#include <vector>

struct APIStruct {
	std::string name;
	std::string rename;
	std::string returnType;
	std::vector<std::string> parameters;
};