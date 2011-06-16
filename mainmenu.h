#ifndef MAINMENU_H
#define MAINMENU_H



#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <vdr/osdbase.h>
#include "actions.h"



class cFolderList : public cOsdMenu
{
public:
    cFolderList();
    ~cFolderList();
    std::string getRomName(std::string GameName);
private:
    eOSState ProcessKey(eKeys Key);
    void createFolders();
};



class cGameList : public cOsdMenu
{
public:
    cGameList(const char *Base=NULL);
    ~cGameList();
private:
    const char* FolderName;
    std::map<std::string, std::string> m_GameMap;
    std::map<std::string, std::string>::const_iterator m_MapIter;
    cActions* Actions;
    bool createGameList();
    eOSState ProcessKey(eKeys Key);
    void FillFolders();
    void Open();
};



#endif


