#include "ImageConfig.h"
#include "ImageData.h"
#include "CsvUtil.h"
#include "CsvData.h"
using std::shared_ptr;
void ImageConfig::init()
{
	auto csvDataMap = std::move(CsvUtil::getInstance()->getDataFromCsv("image.csv"));
	if (csvDataMap.size() < 2)
	{
		return;
	}
	for (int i = 2; i < csvDataMap.size(); i++)
	{
		map<string, Value>& dataMap = csvDataMap.at(i);
		int id = dataMap["id"].asInt();
		string imageName = dataMap["imageName"].asString();

		if (items.find(id) == items.end())
		{
			items[id] = std::make_shared<ImageData>();
		}
		items.at(id)->id = id;
		items.at(id)->imageName = imageName;
	}
}
