#pragma once
#include "cocos2d.h"
#include <string>
class DialogData
{
public:
	DialogData() : id(-1), icon(-1), charImageID(-1), nextID(-1), script("") {};
	DialogData(int id, int icon, int charID, int nextID, std::string& script)
	{
		this->id = id;
		this->icon = icon;
		this->charImageID = charID;
		this->nextID = nextID;
		this->script = script;
	}
	~DialogData() {};
	int id;
	int icon;//对话框图标，-1为无
	int charImageID;
	int nextID;
	std::string script;
};

