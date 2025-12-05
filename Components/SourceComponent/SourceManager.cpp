#include "SourceManager.h"
#include "SourceInternals.h"
#include <string>
#include <vector>

void SourceReplace::RenameText(std::string& filePath, std::vector<std::pair<std::string, std::string>>& APIList) {

	SourceTransform transformer;

	transformer.setFilePath(filePath);
	if (!transformer.LoadFile()) return;
	transformer.ReplaceText(APIList);
	transformer.SaveFile();
}