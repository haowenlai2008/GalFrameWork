#include "DialogConfig.h"
#include "DialogData.h"
#include "CsvUtil.h"
#include "CsvData.h"
using std::shared_ptr;
void DialogConfig::init()
{
	auto csvDataMap = std::move(CsvUtil::getInstance()->getDataFromCsv("dialog.csv"));
	if (csvDataMap.size() < 2)
	{
		return;
	}
	for (int i = 2; i < csvDataMap.size(); i++)
	{
		map<string, Value>& dataMap = csvDataMap.at(i);
		int id = dataMap["id"].asInt();
		int icon = dataMap["icon"].asInt();
		int charImageID = dataMap["charImageID"].asInt();
		int nextID = dataMap["nextID"].asInt();
		string script = dataMap["script"].asString();

		if (items.find(id) == items.end())
		{
			items[id] = std::make_shared<DialogData>();
		}
		items.at(id)->id = id;
		items.at(id)->icon = icon;
		items.at(id)->charImageID = charImageID;
		items.at(id)->nextID = nextID;
		items.at(id)->script = script;
	}
}
