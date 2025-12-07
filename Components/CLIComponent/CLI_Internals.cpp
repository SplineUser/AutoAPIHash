#include "CLI_Internals.h"
#include <string>
#include <vector>


void HelpMenu::displayHelp() {
    std::cout << R"(
AutoAPIHash - Help Menu
-----------------------

AutoAPIHash is a tool designed to minimize VT score via iterative API hashing.

Usage:
  autoapihash.exe [options]

Options:
  -i <input>     Specify input C/CPP File
  -j             Set path to JSON API File
  -h, --help     Show this help menu

Examples:
  autoapihash.exe -i myfile.cpp -j api_list.json

Note:
  The output will be stored in the output folder! Please do not remove the header file! Its essential for compiling the files!
)";
}

bool ArgsExec::ValidateArgs(int argc, char* argv[]) {
    if (argc < 4) {
        return false;   
    }

    if (std::string(argv[1]) != "-i") {
        return false;
    }

    if (std::string(argv[3]) != "-j") {
        return false;
    }

    return true;
}

