#include <string>
#include <vector>

class SourceTransform {
public:
	void setFilePath(std::string filePath);
	bool LoadFile();
	bool ReplaceText(std::vector<std::pair<std::string, std::string>> APIList);
	bool SaveFile(std::string filePath);
private:
	std::string PerfilePath;
	std::vector<std::string> code_lines;
};
