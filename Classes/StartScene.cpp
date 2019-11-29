#include "StartScene.h"
#include "StringUtil.h"
#include "GameScene.h"
#include "CsvUtil.h"
#include "CsvData.h"
#include "SceneConfig.h"
#include "CharacterConfig.h"
#include "ImageConfig.h"
#include "DialogConfig.h"
Scene* StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{
	if (!Scene::init())
		return false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto bg = Sprite::create("bg.jpg");
	bg->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height - bg->getContentSize().height / 2.0f);
	this->addChild(bg);
	auto startItem = MenuItemImage::create(
		"StartNormal.png",
		"Start_selected.png",
		CC_CALLBACK_1(StartScene::menuStartCallback, this));

	auto continueItem = MenuItemImage::create(
		"ContinueS.png",
		"ContinueP.png",
		CC_CALLBACK_1(StartScene::menuContinueCallback, this));

	auto closeItem = MenuItemImage::create(
		"ExitNormal.png",
		"Exit_selected.png",
		CC_CALLBACK_1(StartScene::menuCloseCallback, this));

	startItem->setPosition(Vec2(origin.x + 3.0f * visibleSize.width / 4.0f, origin.y + 5.0f * visibleSize.height / 7.0f));
	continueItem->setPosition(Vec2(origin.x + 3.0f * visibleSize.width / 4.0f, origin.y + 4.0f * visibleSize.height / 7.0f));
	closeItem->setPosition(Vec2(origin.x + 3.0f * visibleSize.width / 4.0f, origin.y + 3.0f * visibleSize.height / 7.0f));
	auto menu = Menu::create(startItem, continueItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto csv = CsvUtil::getInstance()->getCsv("image.csv");
	for (auto row : csv->m_allLineVec)
	{
		auto cols = row.asValueVector();
		for (auto col : cols)
		{
			log(col.asString().c_str());
		}
	}
	SceneConfig::getInstance()->init();
	CharacterConfig::getInstance()->init();
	ImageConfig::getInstance()->init();
	DialogConfig::getInstance()->init();
	return true;
}

void StartScene::menuStartCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene(0));
}

void StartScene::menuContinueCallback(cocos2d::Ref* pSender)
{
}

void StartScene::menuCloseCallback(cocos2d::Ref* pSender)
{
}
