#include "SceneConfig.h"
#include "SceneData.h"
#include "CsvUtil.h"
#include "CsvData.h"
using std::shared_ptr;
void SceneConfig::init()
{
	auto csvDataMap = std::move(CsvUtil::getInstance()->getDataFromCsv("scene.csv"));
	if (csvDataMap.size() < 2)
	{
		return;
	}
	for (int i = 2; i < csvDataMap.size(); i++)
	{
		map<string, Value>& dataMap = csvDataMap.at(i);
		int id = dataMap["id"].asInt();
		int bgID = dataMap["bgID"].asInt();
		int dialogID = dataMap["dialogID"].asInt();
		string script = dataMap["script"].asString();
		int fatherID = dataMap["fatherID"].asInt();
		
		if (fatherID != -1)
		{
			if (items.find(fatherID) == items.end())
			{
				items[fatherID] = std::make_shared<SceneData>();
			}
			items.at(fatherID)->childScenes.push_back(id);
		}
		if (items.find(id) == items.end())
		{
			items[id] = std::make_shared<SceneData>();
		}
		items.at(id)->id = id;
		items.at(id)->bgID = bgID;
		items.at(id)->dialogID = dialogID;
		items.at(id)->script = script;	
	}

}
