#include "JSONConfigManager.h"
#include "JSONInternals.h"
#include <string>
#include <vector>
#include <iostream>



bool JSONConfigManager::LoadConfig(std::string& filePath) {
	JSONVerifier mJV;

	bool Verified = mJV.VerifyStruct(filePath);
	if (!Verified) {
		std::cout << "JSON File Invalid. Please ensure the structure of the JSON!" << std::endl;
		return false;
	}

	JSONParser mJP;
	PerapiList = mJP.ParseJson(filePath);
	std::cout << "JSON File Loaded!" << std::endl;
	return true;
}

std::vector<std::string> getAPIList(){
	std::vector<std::string> APIList;
	for (auto& k : PerapiList) {
		APIList.push_back(k.name);
	}
	return APIList;
}

APIStruct getAPIStruct(std::string& apiName) {
	for (auto& api : PerapiList) {
		if (api.name == apiName) {
			return api;
		}
	}
}