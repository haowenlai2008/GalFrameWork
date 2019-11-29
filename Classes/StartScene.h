#pragma once
#include "cocos2d.h"
USING_NS_CC;
class StartScene : public Scene
{
public:
	CREATE_FUNC(StartScene);
	static Scene* createScene();
	virtual bool init() override;
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuContinueCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);

};

