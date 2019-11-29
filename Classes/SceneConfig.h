#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "ConfigBase.h"
USING_NS_CC;
class SceneData;
class SceneConfig : public virtual Singleton< SceneConfig>, public virtual ConfigBase<SceneData>
{
public:
	friend class Singleton< SceneConfig>;
	friend class ConfigBase<SceneData>;
	virtual void init() override;
	virtual ~SceneConfig() {};
};

