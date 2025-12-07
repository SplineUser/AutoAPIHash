#include "Components/JSONComponent/JSONConfigManager.h"
#include "Components/JSONComponent/APIStruct.h"
#include "Components/SourceComponent/SourceManager.h"
#include "Components/StubComponent/StubManager.h"
#include "Components/CLIComponent/CLI_Interface.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


bool PrependSourceHeader(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        return false;
    }

    std::string original((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());
    in.close();

    std::string updated = "#include \"Stub_Header.h\"\n\n" + original;

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) {
        return false;
    }

    out << updated;
    out.close();
    return true;
}

bool CompileGeneratedCode(const std::string& cppFile) {
    std::string cmd =
        R"(C:\Users\Priyan\source\repos\Import_Table_Reducer\x64\Debug\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r4\mingw64\bin\g++.exe )" + cppFile +" -o payload.exe";

    return system(cmd.c_str()) == 0;
}


int main(int argc, char* argv[]) {
    CLI_Interface cliI;
    if (!cliI.CLIRun(argc, argv)) {
        return 0;
    }
    std::string JSONfilePath = argv[4];
    std::string SourcefilePath = argv[2];
    std::string StubfilePath = argv[6];

    JSONConfigManager mJCM;
    SourceReplace mSR;
    StubManager mStubR;

    bool res = PrependSourceHeader(SourcefilePath);
    if (!res) {
        std::cout << "Error prepending" << std::endl;
    }


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

    CompileGeneratedCode(SourcefilePath);

    return 0;
}