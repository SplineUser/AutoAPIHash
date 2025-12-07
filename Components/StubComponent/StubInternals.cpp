#include "StubInternals.h"
#include "../JSONComponent/APIStruct.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>


void APIDetector::ParseSource(std::string SourcefilePath) {
	std::ifstream sf(SourcefilePath);
	std::string line;

	if (!sf.is_open()) {
		std::cerr << "Error opening: " << SourcefilePath << "\n";
		return;
	}

	while (std::getline(sf, line)) {
		SourceLines.push_back(line);
	}
}

std::vector<std::string> APIDetector::FindAPI(std::vector<std::pair<std::string, std::string>>& APIList) {
    std::unordered_set<std::string> detected;

    for (const auto& api : APIList) {
        for (const auto& line : SourceLines) {
            size_t pos = 0;
            while ((pos = line.find(api.first, pos)) != std::string::npos) {
                detected.insert(api.first);
                pos += api.first.length();
            }
        }
    }

    return std::vector<std::string>(detected.begin(), detected.end());
}




std::vector<std::string> StubCreator::CreateStub(const APIStruct& apiS)
{
    std::vector<std::string> stubs;

    std::string paramList;
    for (size_t i = 0; i < apiS.parameters.size(); i++) {
        paramList += apiS.parameters[i];
        if (i < apiS.parameters.size() - 1)
            paramList += ", ";
    }
    std::string typedefLine =
        "typedef " + apiS.returnType + " (WINAPI* " + "m"+apiS.rename + ")(" + paramList + ");";
    std::string resolverLine =
        "m"+apiS.rename + " " + apiS.rename + " = (" + "m"+apiS.rename + ")ResolveProcByHash("
        "FetchModuleBaseByName(L\"" + apiS.ModuleName + "\"), "
        + std::to_string(apiS.hash) + ");";

    stubs.push_back(typedefLine);
    stubs.push_back(resolverLine);

    return stubs;
}



/* STUB EXAMPLE:

typedef SC_HANDLE(WINAPI* OS)(SC_HANDLE, LPCWSTR, DWORD);
OS mOS = (OS)APIHashing::ResolveProcByHash(APIHashing::FetchModuleBaseByName(L"Advapi32.dll"), 2088786143);

*/


bool StubCreator::WriteStub(const std::string& StubFilePath, const std::vector<std::string>& stub)
{
    std::ofstream outFile(StubFilePath, std::ios::app);

    if (!outFile.is_open())
        return false; 

    for (const auto& line : stub)
        outFile << line << "\n";

    outFile << "\n"; 

    outFile.close();
    return true;
}
