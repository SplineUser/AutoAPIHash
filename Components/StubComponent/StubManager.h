#include "../JSONComponent/APIStruct.h"
#include <string>
#include <vector>

class StubManager {
public:
    bool WriteAllStubs(std::string SourcefilePath,
        std::vector<std::pair<std::string, std::string>>& APIList,
        std::vector<APIStruct> apiSList,
        std::string StubFilePath);
};
