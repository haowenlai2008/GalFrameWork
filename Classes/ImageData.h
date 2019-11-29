#pragma once
#include "cocos2d.h"
#include <string>
class ImageData
{
public:
	ImageData() : id(-1), imageName("") {};
	~ImageData() {};
	ImageData(int id, std::string& imageName)
	{
		this->id = id;
		this->imageName = imageName;
	}
	int id;
	std::string imageName;
};

