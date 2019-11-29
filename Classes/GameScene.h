#pragma once
#include "cocos2d.h"
USING_NS_CC;
class DialogBoxZero;
class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	static Scene* createScene(int sceneID);
	virtual bool init() override;
	void listenInit();
	void nextSentence();
	void nextScene(int sceneID);
	void onMouseDown(Event* event);
	void onKeyDown(EventKeyboard::KeyCode keyCode, Event* event);
	void generateButton(std::vector<int>& childScenes);
	int currentSceneID;
	int currentSentenceID;
	Node* bottomList;
	Sprite* backGround;
	Sprite* character;
	DialogBoxZero* dialogBox;
};

