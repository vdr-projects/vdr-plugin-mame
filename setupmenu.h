#ifndef SETUPMENU_H
#define SETUPMENU_H



#include <vdr/plugin.h>
#include <string>



class cMameSetup
{
public:
    cMameSetup();
    ~cMameSetup();
    int GeneralStopVDR;
    char PathRom[255];
};



class cSetupMenu : public cMenuSetupPage
{
public:
    cSetupMenu();
    ~cSetupMenu();
private:
    cMameSetup m_tmpSetup;
protected:
    virtual void Store();
};



extern cMameSetup g_MameSetup;



#endif
