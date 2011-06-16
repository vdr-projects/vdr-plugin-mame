#include "mainmenu.h"



using namespace std;



cFolderList::cFolderList() : cOsdMenu("MAME")
{
    createFolders();
}



cFolderList::~cFolderList()
{}



void cFolderList::createFolders()
{
    //Create first folder "#", and "A - Z" with ASCII-Code
    cOsdItem* Folder = new cOsdItem("#");
    Add(Folder);

    for (int i = 65; i < 91; i++)
    {
        char FolderName[1];
        sprintf(FolderName, "%c", i);
        cOsdItem* Folder = new cOsdItem(FolderName);
        Add(Folder);
    }
    SetHelp(tr("Open"));
}



eOSState cFolderList::ProcessKey(eKeys Key)
{
    cOsdItem* Item = (cOsdItem*)Get(Current());
    eOSState state = cOsdMenu::ProcessKey(Key);
    if (!HasSubMenu())
    {
        switch (Key)
        {
        case kOk:
            AddSubMenu(new cGameList(Item->Text()));
            break;
        case kRed:
            AddSubMenu(new cGameList(Item->Text()));
            break;
        default:
            break;
        }
    }
    return state;
}






cGameList::cGameList(const char* Base) : cOsdMenu(Base), FolderName(Base)
{
    Actions = new cActions;
    createGameList();
    FillFolders();
}



cGameList::~cGameList()
{
    delete Actions;
}



bool cGameList::createGameList()
{
    string TempLine;
    string GameName;
    string RomName;
    int GameName_Begin;
    int GameName_End;
    int RomName_Begin;
    int RomName_End;

    //Let mame write it's gamelist to /tmp/vdr-mamelist and try to open it
    system("export DISPLAY=:0.0 && sdlmame -listfull > /tmp/vdr-mamelist");
    fstream File;
    File.open("/tmp/vdr-mamelist", ios_base::in);
    m_GameMap.clear();

    if (!File)
    {
        return false;
    }

    while (!File.eof())
    {
        getline(File, TempLine);

        //skip empty lines
        if (TempLine.empty())
        {
            continue;
        }

        //Find entry positions in the line
        RomName_Begin = 0;
        RomName_End = TempLine.find_first_of(" ", RomName_Begin);
        GameName_Begin = TempLine.find_first_not_of(" ", RomName_End + 1) + 1;
        GameName_End = TempLine.size() - 1;

        //Get the game and romname from the line
        RomName = TempLine.substr(RomName_Begin, RomName_End);
        GameName = TempLine.substr(GameName_Begin, GameName_End - GameName_Begin);

        //Skip comments
        if (RomName == "Name:" || RomName == "Description:")
        {
            continue;
        }

        //Create a new entry in the gamemap
        m_GameMap[GameName] = RomName;
    }

    return true;
}



eOSState cGameList::ProcessKey(eKeys Key)
{
    eOSState state=cOsdMenu::ProcessKey(Key);
    switch (Key)
    {
    case kOk:
        Open();
        state = osEnd;
        break;
    case kRed:
        Open();
        state = osEnd;
        break;
    default:
        break;
    }
    return state;
}



void cGameList::FillFolders()
{
    //Walk through m_GameMap, and compare the foldername with the first letter of the
    //game, converted to uppercase
    //If the foldername is "#", check the first character is a digit
    for (m_MapIter = m_GameMap.begin(); m_MapIter != m_GameMap.end(); ++m_MapIter)
    {
        if (FolderName[0] == '#' && isdigit(m_MapIter->first[0]))
        {
            cOsdItem* GameName = new cOsdItem((m_MapIter->first).c_str());
            Add(GameName);
        }

        if (toupper(m_MapIter->first[0]) == FolderName[0])
        {
            cOsdItem* GameName = new cOsdItem((m_MapIter->first).c_str());
            Add(GameName);
        }
    }

    SetHelp(tr("Play"));
}



void cGameList::Open()
{
    cOsdItem* Item = (cOsdItem*)Get(Current());
    stringstream SelectedGame;
    SelectedGame << Item->Text();

    Actions->Play(m_GameMap[SelectedGame.str()]);
}

