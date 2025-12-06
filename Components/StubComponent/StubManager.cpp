#include "StubManager.h"
#include "StubInternals.h"
#include "../JSONComponent/APIStruct.h"
#include <vector>
#include <string>
#include <unordered_set>

bool StubManager::WriteAllStubs(std::string SourcefilePath,
    std::vector<std::pair<std::string, std::string>>& APIList,
    std::vector<APIStruct> apiSList,
    std::string StubFilePath)
{
    APIDetector::ParseSource(SourcefilePath);
    std::vector<std::string> apiFoundList = APIDetector::FindAPI(APIList);

    std::unordered_set<std::string> foundSet(apiFoundList.begin(), apiFoundList.end());
    std::unordered_set<std::string> written;
    bool wroteAnything = false;

    for (auto& apiStruct : apiSList) {
        if (foundSet.find(apiStruct.name) != foundSet.end()) {
            if (written.find(apiStruct.name) != written.end()) continue;

            std::vector<std::string> createdStub = StubCreator::CreateStub(apiStruct);
            bool result = StubCreator::WriteStub(StubFilePath, createdStub);

            if (!result) return false;

            written.insert(apiStruct.name);
            wroteAnything = true;
        }
    }

    return wroteAnything;
}
