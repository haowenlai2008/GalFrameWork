#pragma once
#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;
class StringUtil : public Singleton<StringUtil>
{
public:
	friend class Singleton<StringUtil>;
	ValueVector split(const char* srcStr, const char* sSep);
};

