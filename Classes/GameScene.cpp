#include "GameScene.h"
#include "DialogBoxZero.h"
#include "SceneConfig.h"
#include "CharacterConfig.h"
#include "ImageConfig.h"
#include "DialogConfig.h"
#include "CharacterData.h"
#include "DialogData.h"
#include "ImageData.h"
#include "SceneData.h"
#include "UIUtil.h"
#include "Bottom.h"

Scene* GameScene::createScene(int sceneID)
{
	auto scene = GameScene::create();
	scene->currentSceneID = sceneID;
	scene->currentSentenceID = 0;
	return scene;
}

bool GameScene::init()
{
	listenInit();
	dialogBox = DialogBoxZero::create();
	this->addChild(dialogBox, 2);
	auto sceneConfig = SceneConfig::getInstance();
	auto imageConfig = ImageConfig::getInstance();
	auto dialogConfig = DialogConfig::getInstance();
	auto characterConfig = CharacterConfig::getInstance();

	auto sceneData = sceneConfig->getItem(currentSceneID);
	auto bgImageData = imageConfig->getItem(sceneData.bgID);
	auto backGroundName = bgImageData.imageName;
	backGround = Sprite::create(backGroundName);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto targetSize = UIUtil::getInstance()->getAdaptiveSize(backGround->getContentSize(), visibleSize);
	backGround->setContentSize(targetSize);
	backGround->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(backGround, 0);
	//currentSentenceID = sceneData.dialogID;
	auto dialogData = dialogConfig->getItem(currentSentenceID);
	dialogBox->showDialog(dialogData.script);
	auto charTexName = imageConfig->getItem(dialogData.charImageID).imageName;

	character = Sprite::create(charTexName);
	character->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + character->getContentSize().height / 2));
	this->addChild(character, 1);

	bottomList = Node::create();
	bottomList->setPosition(Vec2::ZERO);
	this->addChild(bottomList, 4);
	return true;
}

void GameScene::listenInit()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto mouseListener = EventListenerMouse::create();//注册监听
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene::nextSentence()
{
	auto sceneConfig = SceneConfig::getInstance();
	auto imageConfig = ImageConfig::getInstance();
	auto dialogConfig = DialogConfig::getInstance();
	auto characterConfig = CharacterConfig::getInstance();
	if (dialogBox->isFinish())
	{
		int nextSentenceID = dialogConfig->getItem(currentSentenceID).nextID;
		if (nextSentenceID != -1)//是否有下一句，有下一句就继续放
		{	
			dialogBox->reset();
			currentSentenceID = nextSentenceID;
			auto dialogData = dialogConfig->getItem(currentSentenceID);
			if (dialogData.icon != -1)
			{
				auto iconImageData = imageConfig->getItem(dialogData.icon);
				dialogBox->showDialog(dialogData.script, iconImageData.imageName);
			}
			else
			{
				dialogBox->showDialog(dialogData.script);
			}
			auto nextImageData = imageConfig->getItem(dialogData.charImageID);
			character->setTexture(nextImageData.imageName);
		}
		else//没下一句就看看有没有下一个场景
		{
			auto sceneData = sceneConfig->getItem(currentSceneID);
			if (sceneData.childScenes.size() > 0)
			{
				if (sceneData.childScenes.size() > 1)
					generateButton(sceneData.childScenes);
				else
				{
					if (sceneConfig->getItem(sceneData.childScenes[0]).script != "")
						generateButton(sceneData.childScenes);
					else
						nextScene(sceneData.childScenes[0]);
				}
			}
		}
	}
}

void GameScene::nextScene(int sceneID)
{
	currentSceneID = sceneID;
	auto sceneConfig = SceneConfig::getInstance();
	auto imageConfig = ImageConfig::getInstance();
	auto dialogConfig = DialogConfig::getInstance();
	auto characterConfig = CharacterConfig::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sceneData = sceneConfig->getItem(currentSceneID);
	auto bgImageData = imageConfig->getItem(sceneData.bgID);
	auto backGroundName = bgImageData.imageName;
	currentSentenceID = sceneData.dialogID;

	auto targetSize = UIUtil::getInstance()->getAdaptiveSize(backGround->getContentSize(), visibleSize);
	backGround->setContentSize(targetSize);

	dialogBox->reset();
	auto dialogData = dialogConfig->getItem(currentSentenceID);
	dialogBox->showDialog(dialogData.script);
	auto charTexName = imageConfig->getItem(dialogData.charImageID).imageName;
	character->setTexture(charTexName);
}

void GameScene::onMouseDown(Event* event)
{
	EventMouse* e = (EventMouse*)event;			//获得鼠标事件指针
	Vec2 realPosition = Vec2(e->getCursorX(), e->getCursorY());
	if (dialogBox->isTouch(realPosition))
		nextSentence();
}

void GameScene::onKeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		nextSentence();
	}
}

void GameScene::generateButton(std::vector<int>& childScenes)
{
	bottomList->removeAllChildren();
	auto sceneConfig = SceneConfig::getInstance();
	auto imageConfig = ImageConfig::getInstance();
	auto dialogConfig = DialogConfig::getInstance();
	auto characterConfig = CharacterConfig::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	Vec2 center(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	float yUnit = visibleSize.height / 6.0f;
	Vec2 startPoint(center.x, center.y + childScenes.size() * yUnit / 2.0f);
	Vector<MenuItem*> itemList;
	for (int i = 0; i < childScenes.size(); i++)
	{
		auto sceneData = sceneConfig->getItem(childScenes[i]);
		auto pos = startPoint - Vec2(0.0f, yUnit * i);
		auto jump = std::bind(&GameScene::nextScene, this, sceneData.id);
		auto bottom = Bottom::create(sceneData.script, [this, sceneData](Ref*) { bottomList->removeAllChildrenWithCleanup(true); this->nextScene(sceneData.id); });
		bottom->setPosition(pos);
		itemList.pushBack(bottom);
		
	}
	Menu* menu = Menu::createWithArray(itemList);
	menu->setPosition(Vec2::ZERO);
	bottomList->addChild(menu);
}
