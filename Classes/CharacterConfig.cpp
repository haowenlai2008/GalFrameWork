#include "CharacterConfig.h"
#include "CharacterData.h"
#include "CsvUtil.h"
#include "CsvData.h"
using std::shared_ptr;
void CharacterConfig::init()
{
	auto csvDataMap = std::move(CsvUtil::getInstance()->getDataFromCsv("character.csv"));
	if (csvDataMap.size() < 2)
	{
		return;
	}
	for (int i = 2; i < csvDataMap.size(); i++)
	{
		map<string, Value>& dataMap = csvDataMap.at(i);
		int id = dataMap["id"].asInt();
		string name = dataMap["name"].asString();

		if (items.find(id) == items.end())
		{
			items[id] = std::make_shared<CharacterData>();
		}
		items.at(id)->id = id;
		items.at(id)->name = name;
	}
}
