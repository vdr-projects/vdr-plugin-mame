#include <vdr/plugin.h>
#include "mainmenu.h"
#include "setupmenu.h"



static const char *VERSION        = "0.0.1";
static const char *DESCRIPTION    = "MAME emulator";
static const char *MAINMENUENTRY  = "MAME";

class cPluginMame : public cPlugin
{
private:
public:
    cPluginMame(void);
    virtual ~cPluginMame();
    virtual const char *Version(void)
    {
        return VERSION;
    }
    virtual const char *Description(void)
    {
        return DESCRIPTION;
    }
    virtual const char *CommandLineHelp(void);
    virtual bool ProcessArgs(int argc, char *argv[]);
    virtual bool Initialize(void);
    virtual bool Start(void);
    virtual void Stop(void);
    virtual void Housekeeping(void);
    virtual void MainThreadHook(void);
    virtual cString Active(void);
    virtual const char *MainMenuEntry(void)
    {
        return MAINMENUENTRY;
    }
    virtual cOsdObject *MainMenuAction(void);
    virtual cMenuSetupPage *SetupMenu(void);
    virtual bool SetupParse(const char *Name, const char *Value);
    virtual bool Service(const char *Id, void *Data = NULL);
    virtual const char **SVDRPHelpPages(void);
    virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
};



cPluginMame::cPluginMame(void)
{
    // Initialize any member variables here.
    // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
    // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}



cPluginMame::~cPluginMame()
{
    // Clean up after yourself!
}



const char *cPluginMame::CommandLineHelp(void)
{
    // Return a string that describes all known command line options.
    return NULL;
}



bool cPluginMame::ProcessArgs(int argc, char *argv[])
{
    // Implement command line argument processing here if applicable.
    return true;
}



bool cPluginMame::Initialize(void)
{
    // Initialize any background activities the plugin shall perform.
    return true;
}



bool cPluginMame::Start(void)
{
    // Start any background activities the plugin shall perform.
    return true;
}



void cPluginMame::Stop(void)
{
    // Stop any background activities the plugin shall perform.
}



void cPluginMame::Housekeeping(void)
{
    // Perform any cleanup or other regular tasks.
}



void cPluginMame::MainThreadHook(void)
{
    // Perform actions in the context of the main program thread.
    // WARNING: Use with great care - see PLUGINS.html!
}



cString cPluginMame::Active(void)
{
    // Return a message string if shutdown should be postponed
    return NULL;
}



cOsdObject *cPluginMame::MainMenuAction(void)
{
    return new cFolderList();
}



cMenuSetupPage *cPluginMame::SetupMenu(void)
{
    return new cSetupMenu();
}



bool cPluginMame::SetupParse(const char *Name, const char *Value)
{
    if      (!strcasecmp(Name, "GeneralStopVDR"))  g_MameSetup.GeneralStopVDR = atoi(Value);
    else if (!strcasecmp(Name, "PathRom"))         strn0cpy(g_MameSetup.PathRom, Value, sizeof(g_MameSetup.PathRom));
    else
        return false;

    return true;
}



bool cPluginMame::Service(const char *Id, void *Data)
{
    // Handle custom service requests from other plugins
    return false;
}



const char **cPluginMame::SVDRPHelpPages(void)
{
    // Return help text for SVDRP commands this plugin implements
    return NULL;
}



cString cPluginMame::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
    // Process SVDRP commands this plugin implements
    return NULL;
}



VDRPLUGINCREATOR(cPluginMame); // Don't touch this!
