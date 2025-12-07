#include "StubManager.h"
#include "StubInternals.h"
#include "../JSONComponent/APIStruct.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

bool StubManager::WriteAllStubs(std::string SourcefilePath,
    std::vector<std::pair<std::string, std::string>>& APIList,
    std::vector<APIStruct> apiSList,
    std::string StubFilePath)
{
    APIDetector detector;
    detector.ParseSource(SourcefilePath);
    std::vector<std::string> apiFoundList = detector.FindAPI(APIList);

    std::unordered_set<std::string> foundSet(apiFoundList.begin(), apiFoundList.end());
    std::unordered_set<std::string> written;
    bool wroteAnything = false;

    StubCreator creator;

    for (auto& apiStruct : apiSList) {
        // Only write stubs for APIs that were found in the source
        if (foundSet.find(apiStruct.name) != foundSet.end()) {
            // Skip if we already wrote this API
            if (written.find(apiStruct.name) != written.end()) continue;

            std::vector<std::string> createdStub = creator.CreateStub(apiStruct);
            bool result = creator.WriteStub(StubFilePath, createdStub);

            if (!result) return false; // Stop if writing fails

            written.insert(apiStruct.name);
            std::cout << "* Hashing API: " << apiStruct.name << std::endl;
            wroteAnything = true;
        }
    }

    return wroteAnything;
}
