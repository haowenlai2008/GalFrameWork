/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	//获得屏幕尺寸
    Size visibleSize = Director::getInstance()->getVisibleSize();
	//获得原点坐标
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.


    //创建按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));


    float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
    float y = origin.y + closeItem->getContentSize().height/2;
    closeItem->setPosition(Vec2(x,y));

    //创建菜单
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//创建文本
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

	//创建精灵
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);

	//创建精灵
	shinobu = Sprite::create("shinobu.jpg");
	shinobu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(shinobu);

	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* keyListener = EventListenerKeyboard::create();//创建键盘按键监听器 
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::Press, this);//设置按键按下的响应 
	keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::Release, this);//设置按键释放的响应 
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(HelloWorld::MouseDown, this);
	listener->onMouseUp = CC_CALLBACK_1(HelloWorld::MouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::Press(EventKeyboard::KeyCode keycode, Event* event)
{
	using KC = EventKeyboard::KeyCode;
	switch (keycode)
	{
	case KC::KEY_UP_ARROW://上按键
		log("up press");
		shinobu->runAction(MoveBy::create(0.5f, Vec2(0.0f, 10.0f)));
		break;
	case KC::KEY_DOWN_ARROW://下按键
		log("down press");
		shinobu->runAction(MoveBy::create(0.5f, Vec2(0.0f, -10.0f)));
		break;
	case KC::KEY_RIGHT_ARROW://右按键
		log("right press");
		shinobu->runAction(MoveBy::create(0.5f, Vec2(10.0f, 0.0f)));
		break;
	case KC::KEY_LEFT_ARROW://左按键
		log("left press");
		shinobu->runAction(MoveBy::create(0.5f, Vec2(-10.0f, 0.0f)));
		break;
	case KC::KEY_Z:
		log("Explosion!");
		shinobu->runAction(JumpBy::create(0.5f, Vec2(0.0f, 10.0f), 20.0f, 1));
		break;
	default:
		break;
	}
}

void HelloWorld::Release(EventKeyboard::KeyCode keycode, Event* event)
{
	using KC = EventKeyboard::KeyCode;
	switch (keycode)
	{
	case KC::KEY_UP_ARROW:
		log("up release");
		break;
	case KC::KEY_DOWN_ARROW:
		log("down release");
		break;
	case KC::KEY_RIGHT_ARROW:
		log("right release");
		break;
	case KC::KEY_LEFT_ARROW:
		log("left release");
		break;
	case KC::KEY_Z:
		log("Boom!");
		break;
	default:
		break;
	}
}

void HelloWorld::MouseDown(cocos2d::Event* event)
{
	EventMouse* e = static_cast<EventMouse*>(event);
	log("press (%f, %f)", e->getCursorX(), e->getCursorY());
}

void HelloWorld::MouseUp(cocos2d::Event* event)
{
	EventMouse* e = static_cast<EventMouse*>(event);
	log("release (%f, %f)", e->getCursorX(), e->getCursorY());
}
