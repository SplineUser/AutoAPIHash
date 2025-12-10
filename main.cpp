#include "Components/JSONComponent/JSONConfigManager.h"
#include "Components/JSONComponent/APIStruct.h"
#include "Components/SourceComponent/SourceManager.h"
#include "Components/StubComponent/StubManager.h"
#include "Components/CLIComponent/CLI_Interface.h"
#include "Helper/LoadAPI.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

bool file_exists(const string& path)
{
    struct stat buffer {};
    return (stat(path.c_str(), &buffer) == 0);
}

bool PrependSourceHeader(const string& filePath)
{
    if (!file_exists(filePath)) return false;

    ifstream in(filePath);
    if (!in.is_open()) return false;

    string original((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    ofstream out(filePath, ios::trunc);
    if (!out.is_open()) return false;

    out << "#include \"Stub_Header.h\"\n\n" << original;
    out.close();
    return true;
}

bool CompileGeneratedCode(const string& cppFile)
{
    string cmd = R"(".\compiler\winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r4\mingw64\bin\g++.exe" )"
        + cppFile + " -static -static-libgcc -static-libstdc++ -o output.exe";

    cout << "[+] Compiling with MinGW...\nCMD = " << cmd << endl;
    return system(cmd.c_str()) == 0;
}

bool RunVirusTotalScan(const string& filePath, const string& apiKey)
{
    if (apiKey.empty() || !file_exists(filePath)) return false;

    system("python3 -m pip install requests --quiet");
    string cmd = "python3 vt_scan.py -file \"" + filePath + "\" -key \"" + apiKey + "\"";

    cout << "\n[+] Running VirusTotal scan...\nCMD = " << cmd << endl;
    return system(cmd.c_str()) == 0;
}

int main(int argc, char* argv[])
{
    CLI_Interface cli;
    if (!cli.CLIRun(argc, argv) || argc < 7) return 1;

    string sourceFile = argv[2];
    string jsonFile = argv[4];
    string stubFile = argv[6];

    LoadAPI apiLoader;
    string APIKey;
    apiLoader.APILoad("Paste_VT_API_Key.txt", APIKey);

    if (!PrependSourceHeader(sourceFile)) return 1;

    JSONConfigManager jsonManager;
    if (!jsonManager.LoadConfig(jsonFile)) return 1;

    vector<pair<string, string>> APIList = jsonManager.getAPIList();
    SourceReplace replacer;
    replacer.RenameText(sourceFile, APIList);

    vector<APIStruct> apiStructs;
    for (auto& api : APIList)
        apiStructs.push_back(jsonManager.getAPIStruct(api.first));

    StubManager stubWriter;
    stubWriter.WriteAllStubs(sourceFile, APIList, apiStructs, stubFile);

    if (!CompileGeneratedCode(sourceFile)) return 1;

    bool runVT = false;
    for (int i = 1; i < argc; ++i)
        if (string(argv[i]) == "-v") { runVT = true; break; }

    if (runVT && !APIKey.empty())
        RunVirusTotalScan("output.exe", APIKey);

    return 0;
}
