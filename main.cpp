#include "Components/JSONComponent/JSONConfigManager.h"
#include "Components/JSONComponent/APIStruct.h"
#include "Components/SourceComponent/SourceManager.h"
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string JSONfilePath = "C:\\Users\\Priyan\\source\\repos\\Import_Table_Reducer\\x64\\Debug\\api_list.json";
    std::string SourcefilePath = "C:\\Users\\Priyan\\source\\repos\\Import_Table_Reducer\\x64\\Debug\\FileLocation.cpp";

    JSONConfigManager mJCM;
    SourceReplace mSR;

    mJCM.LoadConfig(JSONfilePath);

    auto APIList = mJCM.getAPIList();
    mSR.RenameText(SourcefilePath, APIList);

    return 0;
}