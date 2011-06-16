#include "setupmenu.h"



using namespace std;



cMameSetup g_MameSetup;



cMameSetup::cMameSetup()
{
    GeneralStopVDR = true;
    strncpy(PathRom, "/usr/local/share/mame/roms", sizeof(PathRom));
}



cMameSetup::~cMameSetup()
{}



cSetupMenu::cSetupMenu() : m_tmpSetup(g_MameSetup)
{
    static const char Allowed[] = "aäbcdefghijklmnoöpqrstuüvwxyz0123456789-+_@/&.";
    Add(new cMenuEditBoolItem(tr("Stop VDR before play"), &m_tmpSetup.GeneralStopVDR, tr("no"), tr("yes")));
    Add(new cMenuEditStrItem(tr("Rom Path"), m_tmpSetup.PathRom, 255, Allowed));
}



cSetupMenu::~cSetupMenu()
{}



void cSetupMenu::Store()
{
    g_MameSetup = m_tmpSetup;
    SetupStore("GeneralStopVDR", g_MameSetup.GeneralStopVDR);
    SetupStore("PathRom", g_MameSetup.PathRom);
}
