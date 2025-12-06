#pragma once
#include "../JSONComponent/APIStruct.h"
#include <string>
#include <vector>

class APIDetector {
public:
    void ParseSource(std::string SourcefilePath);
    std::vector<std::string> FindAPI(std::vector<std::pair<std::string, std::string>>& APIList);

private:
    std::vector<std::string> SourceLines;
};

class StubCreator {
public:
    std::vector<std::string> CreateStub(const APIStruct& apiS);
    bool WriteStub(const std::string& StubFilePath, const std::vector<std::string>& stub);
};
