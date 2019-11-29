#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "ConfigBase.h"
USING_NS_CC;
class CharacterData;
class CharacterConfig : public virtual Singleton< CharacterConfig>, public virtual ConfigBase<CharacterData>
{
public:
	friend class Singleton< CharacterConfig>;
	virtual void init() override;
	virtual ~CharacterConfig() {};
};

