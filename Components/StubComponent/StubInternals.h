#include "../JSONComponent/APIStruct.h"
#include <string>
#include <vector>

class APIDetector {
public:
	void ParseSource(std::string SourcefilePath);
	std::vector<std::string> FindAPI(const std::vector<std::pair<std::string, std::string>>& APIList);
private:
	std::vector<std::string> SourceLines;
};

class StubCreator {
public:
	std::vector<std::string> CreateStub(APIStruct apiS);
	bool WriteStub(std::string StubFilePath, std::string stub);
}

