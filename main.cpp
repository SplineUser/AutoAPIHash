#include "Components/JSONComponent/JSONConfigManager.h"
#include "Components/JSONComponent/APIStruct.h"
#include "Components/SourceComponent/SourceManager.h"
#include "Components/StubComponent/StubManager.h"
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string JSONfilePath = "C:\\Users\\Priyan\\source\\repos\\Import_Table_Reducer\\x64\\Debug\\api_list.json";
    std::string SourcefilePath = "C:\\Users\\Priyan\\source\\repos\\Import_Table_Reducer\\x64\\Debug\\FileLocation.cpp";
    std::string StubfilePath = "C:\\Users\\Priyan\\source\\repos\\Import_Table_Reducer\\x64\\Debug\\FileLocation.cpp";

    JSONConfigManager mJCM;
    SourceReplace mSR;
    StubManager mStubR;

    mJCM.LoadConfig(JSONfilePath);
    std::vector<std::pair<std::string, std::string>> APIList = mJCM.getAPIList();
    mSR.RenameText(SourcefilePath, APIList);

    std::vector<APIStruct> apiSList;
    for (auto const& api : APIList) {
        std::string apiName = api.first; 
        APIStruct apiS = mJCM.getAPIStruct(apiName);
        apiSList.push_back(apiS);
    }


    mStubR.WriteAllStubs(SourcefilePath, APIList, apiSList, StubfilePath);

    return 0;
}