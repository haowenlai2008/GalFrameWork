#include "CsvUtil.h"
#include "StringUtil.h"
#include "CsvData.h"
void CsvUtil::loadFile(const char* sPath)
{
	CsvData* csvData = CsvData::create();

	std::string str = FileUtils::getInstance()->getStringFromFile("excel/" + std::string(sPath));
	log(str.c_str());
	ValueVector linesList = StringUtil::getInstance()->split(str.c_str(), "\r\n");
	for (int i = 0; i < linesList.size(); i++)
	{
		ValueVector tArr = StringUtil::getInstance()->split(linesList.at(i).asString().c_str(), ",");
		csvData->addLineData(tArr);
	}
	
	auto size = csvData->getRowColNum();
	for (int i = 0; i < size.width; i++)
	{
		for (int j = 0; j < size.height; j++)
		{
			log(csvData->getSingleLineData(i).at(j).asString().c_str());
		}
	}
	log("coco%d", csvData->getRowColNum().height);
	mCsvMap.insert(sPath, csvData);
}

CsvData* CsvUtil::getCsv(const char* csvFilePath)
{
	auto csvData = mCsvMap.at(csvFilePath);
	if (csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}
	return csvData;
}

Value CsvUtil::getValue(int iRow, int iCol, const char* csvFilePath)
{
	auto csvData = mCsvMap.at(csvFilePath);
	if (csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}

	ValueVector rowVector = csvData->getSingleLineData(iRow);
	Value colValue = rowVector.at(iCol);
	return colValue;
}

const std::string CsvUtil::get(int iRow, int iCol, const char* csvFilePath)
{
	return getValue(iRow, iCol, csvFilePath).asString();
}

const int CsvUtil::getInt(int iRow, int iCol, const char* csvFilePath)
{
	return getValue(iRow, iCol, csvFilePath).asInt();
}

const Size CsvUtil::getFileRowColNum(const char* csvFilePath)
{
	auto csvData = mCsvMap.at(csvFilePath);
	if (csvData == nullptr)
	{
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}
	Size size = csvData->getRowColNum();
	return size;
}

const int CsvUtil::findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath)
{
	return 0;
}

std::vector<std::map<string, Value>> CsvUtil::getDataFromCsv(const char* filepath)
{
	vector<std::map<string, Value>> result;
	auto csvdata = this->getCsv(filepath);
	
	auto size = csvdata->getRowColNum();
	/*for (int i = 0; i < size.width; i++)
	{
		for (int j = 0; j < size.height; j++)
		{
			log(csvdata->getSingleLineData(i).at(i).asString().c_str());
		}
	}*/
	std::vector<string> keyList;//¼üÖµÐòÁÐ
	auto keyLineData = csvdata->getSingleLineData(0);
	for (auto dataUnit : keyLineData)
	{
		keyList.push_back(dataUnit.asString());
	}
	result.resize(size.width);
	for (int i = 0; i < size.width; i++)
	{
		auto lineData = csvdata->getSingleLineData(i);
		for (int j = 0; j < size.height; j++)
		{
			string key = keyList[j];
			log(key.c_str());
			log(lineData.at(j).asString().c_str());
			result.at(i)[key] = lineData.at(j);
		}
	}
	return result;
}
