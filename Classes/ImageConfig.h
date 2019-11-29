#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "ConfigBase.h"
USING_NS_CC;
class ImageData;
class ImageConfig : public virtual Singleton<ImageConfig>, public virtual ConfigBase<ImageData>
{
public:
	friend class Singleton<ImageConfig>;
	virtual void init() override;
	virtual ~ImageConfig() {};
};

