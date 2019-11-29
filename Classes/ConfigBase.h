#pragma once
#include "cocos2d.h"
#include <map>
template<class T>
class ConfigBase
{
public:
	virtual T& getItem(int id) 
	{
		return *items[id];
	};
	virtual void init() = 0;
	virtual ~ConfigBase() {};
	ConfigBase() {};
protected:
	std::map<int, std::shared_ptr<T>> items;
	
};
