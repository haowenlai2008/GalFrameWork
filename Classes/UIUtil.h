#pragma once
#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;
class UIUtil : public Singleton<UIUtil>
{
public:
	friend class Singleton<UIUtil>;
	Size getAdaptiveSize(Size origin, Size canvaSize);//将尺寸适配到画布上
};

