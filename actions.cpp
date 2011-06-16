#include "actions.h"



using namespace std;



cActions::cActions()
{}



cActions::~cActions()
{}



void cActions::Play(string RomName)
{
    //Generate the shell-command and execute it
    stringstream Command;
    Command << "vdr-mame-launch.sh ";
    Command << g_MameSetup.GeneralStopVDR << " " << g_MameSetup.PathRom << " " << RomName << " &";

    SystemExec(Command.str().c_str());
}


