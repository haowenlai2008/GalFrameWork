#include "DialogBoxZero.h"
#include "UIUtil.h"
Size DialogBoxZero::getContentSize()
{
	return box->getContentSize();
}
bool DialogBoxZero::init()
{
	auto origin = Director::getInstance()->getVisibleOrigin();

	isHide = false;
	box = Sprite::create("DialogBox.png");
	Size targetSize = UIUtil::getInstance()->getAdaptiveSize(box->getContentSize(), Director::getInstance()->getVisibleSize());
	box->setContentSize(targetSize);
	sentence = Label::createWithSystemFont("A", "Arial", 15);
	sentence->setColor(Color3B::WHITE);
	sentence->setAnchorPoint(Vec2(0, 1));
	sentence->setPosition(Vec2(origin.x + 20,
		box->getContentSize().height - sentence->getContentSize().height));
	
	box->addChild(sentence, 1);
	box->setPosition(Vec2(origin.x + box->getContentSize().width / 2, origin.y + box->getContentSize().height / 2));
	ico = Sprite::create();
	this->addChild(ico,1);
	this->addChild(box);
	this->schedule(schedule_selector(DialogBoxZero::showSentence), 0.02f);//添加定时器
//	listenInit();
	hideDialog();
	return true;
}

bool DialogBoxZero::isTouch(Vec2 position)
{
	return position.y < box->getContentSize().height;
}

bool DialogBoxZero::isFinish()
{
	return charCounter == 0 || charCounter == currentSentence.sentence.size();
}

void DialogBoxZero::reset()
{
	charCounter = 0;
}

void DialogBoxZero::listenInit()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(DialogBoxZero::onKeyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto mouseListener = EventListenerMouse::create();//注册监听
	mouseListener->onMouseDown = CC_CALLBACK_1(DialogBoxZero::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void DialogBoxZero::showDialog(const std::string & sentence)
{
	//sentenceQueue.push(SentenceUnit(sentence, ""));
	currentSentence.sentence = sentence;
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::showDialog(const std::string & sentence, const std::string & texture)
{
	//sentenceQueue.push(SentenceUnit(sentence, texture));
	currentSentence.sentence = sentence;
	currentSentence.ico = texture;
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::showDialog(const std::string & sentence, const std::string & texture, const std::function<void()>& func)
{
	//sentenceQueue.push(SentenceUnit(sentence, texture,func));
	currentSentence.sentence = sentence;
	currentSentence.ico = texture;
	currentSentence.func = func;
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::showDialog(const std::function<void()>& func)
{
	//sentenceQueue.push(SentenceUnit(func));
	currentSentence.func = func;
	if (isHide)
	{
		this->setVisible(true);
	}
}

void DialogBoxZero::hideDialog()
{
	this->setVisible(false);
	isHide = true;
}

void DialogBoxZero::showSentence(float dt)
{
	if (charCounter < currentSentence.sentence.size())
	{
		currentSentence.sentence.begin() + charCounter + 1 == currentSentence.sentence.end() ? charCounter += 1 : charCounter += 2;
		auto head = currentSentence.sentence.begin();
		auto tail = currentSentence.sentence.begin() + charCounter;
		sentence->setString(std::string(head, tail));
	}
}

void DialogBoxZero::onMouseDown(Event * event)
{
	if (this->isVisible())
	{

		EventMouse* e = (EventMouse*)event;			//获得鼠标事件指针
		Vec2 realPosition = Vec2(e->getCursorX(), e->getCursorY());
		if (realPosition.y < box->getContentSize().height)
		{
			if (charCounter < currentSentence.sentence.size())
			{
				charCounter = currentSentence.sentence.size() - 1;
				return;
			}
			charCounter = 0;
			currentSentence.func();
		}
	}
	else
	{
		hideDialog();
	}
}

void DialogBoxZero::onKeyDown(EventKeyboard::KeyCode keyCode, Event * event)
{
	if ( keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		if (this->isVisible())
		{
			if (charCounter < currentSentence.sentence.size())
			{
				charCounter = currentSentence.sentence.size() - 1;
				return;
			}
			charCounter = 0; 
			currentSentence.func();
		}
		else
		{
			hideDialog();
		}
	}
	
}

