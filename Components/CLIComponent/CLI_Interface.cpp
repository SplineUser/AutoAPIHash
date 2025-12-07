#include "CLI_Interface.h"
#include "CLI_Internals.h"

bool CLI_Interface::CLIRun(int argc, char* argv[]) {
	HelpMenu Help_obj;
	ArgsExec Args_obj;


	if (!Args_obj.ValidateArgs(argc, argv)) {
		Help_obj.displayHelp();
		return false;
	}
}