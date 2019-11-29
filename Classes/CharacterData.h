#pragma once
#include "cocos2d.h"
#include <string>
using std::string;
class CharacterData
{
public:
	CharacterData() : id(-1), name("") {};
	~CharacterData() {};
	CharacterData(int id, string& name)
	{
		this->id = id;
		this->name = name;
	};
	int id;
	string name;
};

