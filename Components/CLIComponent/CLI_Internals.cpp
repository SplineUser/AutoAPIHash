#include "CLI_Internals.h"
#include <iostream>
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
  -s             Set path to source header file 
  -h, --help     Show this help menu

Examples:
  autoapihash.exe -i myfile.cpp -j api_list.json -s headerfile.h

Note:
  The output will be stored in the output folder! Please do not remove the header file! Its essential for compiling the files!
)";
}

bool ArgsExec::ValidateArgs(int argc, char* argv[]) {
    if (argc < 6) {
        return false;   
    }

    if (std::string(argv[1]) != "-i") {
        return false;
    }

    if (std::string(argv[3]) != "-j") {
        return false;
    }

    if (std::string(argv[5]) != "-s") {
        return false;
    }

    return true;
}

