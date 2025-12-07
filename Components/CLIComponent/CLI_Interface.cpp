#include "CLI_Interface.h"
#include "CLI_Internals.h"

void CLI_Interface::CLIRun(int argc, char* argv[]) {
	HelpMenu Help_obj;
	ArgsExec Args_obj;

	if (!Help_obj.ValidateArgs(argc, argv)) {
		Args_obj.displayHelp();
	}
}