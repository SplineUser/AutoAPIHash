#include <string>
#include <vector>
#include "APIStruct.h"
#include "JSONInternals.h"

class JSONConfigManager {
public:
	bool LoadConfig(std::string& filePath);
	std::vector<std::pair<std::string, std::string>> getAPIList();
	APIStruct getAPIStruct(std::string& apiName);
private:
	std::vector<APIStruct> PerapiList;
};