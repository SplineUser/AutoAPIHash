#include <string>
#include <vector>

class HelpMenu{
public:
	void displayHelp();
}

class ArgsExec{
public:
	bool ValidateArgs(int argc, char* argv[]);
}