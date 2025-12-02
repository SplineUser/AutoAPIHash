#include <string>
#include <vector>

class JSONConfigManager {
public:
	bool LoadConfig(std::string filePath);
	std::vector <std::string> getAPIList();

};