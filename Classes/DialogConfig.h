#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "ConfigBase.h"
USING_NS_CC;
class DialogData;
class DialogConfig : public virtual Singleton< DialogConfig>, public virtual ConfigBase<DialogData>
{
public:
	friend class Singleton< DialogConfig>;
	virtual void init() override;
	virtual ~DialogConfig() {};
};

