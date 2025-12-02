#pragma once
#include "APIStruct.h"
#include <string>
#include <vector>





class JSONParser {
public:
	std::vector<APIStruct> ParseJson(const std::string& filePath);
};

class JSONVerifier {
public:
	JSONVerifier() : IsValid(false) {}
	bool VerifyStruct(const std::string& filePath);
private:
	bool IsValid;
};

class ConfigMapper {
public:
	void SetAPIList(std::vector<APIStruct>& apiList) {
		APIs = apiList;
	}
	const std::vector<APIStruct>& GetAPIList() const {
		return APIs;
	}

private:
	std::vector<APIStruct> APIs;
};