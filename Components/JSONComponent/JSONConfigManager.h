#include <string>
#include <vector>
#include "JSONInternals.h"

class JSONConfigManager {
public:
	bool LoadConfig(std::string& filePath);
	std::vector <std::string> getAPIList();
	std::vector<APIStruct> getAPIStruct(std::string& apiName);

};