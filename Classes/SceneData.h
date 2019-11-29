#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
class SceneData
{
public:
	SceneData() : id(-1), bgID(-1), dialogID(-1) {};
	~SceneData() {};
	SceneData(int id, int bgID, int dialogID, std::string& script)
	{
		this->id = id;
		this->bgID = bgID;
		this->dialogID = dialogID;
		this->script = script;
	}
	int id;
	int bgID;
	int dialogID;
	std::string script;
	std::vector<int> childScenes;
};

