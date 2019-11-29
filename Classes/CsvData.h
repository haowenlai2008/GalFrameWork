#pragma once
#include "cocos2d.h"
using cocos2d::ValueVector;
using cocos2d::Value;
using cocos2d::Size;
class CsvData : public cocos2d::Ref
{
public:
	CREATE_FUNC(CsvData);
	virtual bool init();
	void addLineData(ValueVector lineData);
	ValueVector getSingleLineData(int iLine);
	Size getRowColNum();
	ValueVector m_allLineVec;
};

