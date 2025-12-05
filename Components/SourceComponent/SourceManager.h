#include <vector>
#include <string>

class SourceReplace {
public:
	bool RenameText(std::string& filePath, std::vector<std::pair<std::string, std::string>>& APIList);
};