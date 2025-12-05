#include <string>
#include <vector>

class SourceTransform {
public:
	void setFilePath(std::string filePath);
	bool LoadFile();
	bool ReplaceText(const std::vector<std::pair<std::string, std::string>>& APIList);
	bool SaveFile();
private:
	std::string PerfilePath;
	std::vector<std::string> code_lines;
};
