#pragma once
#include "cocos2d.h"
#include "Singleton.h"
USING_NS_CC;
using std::vector;
using std::map;
using std::string;
using cocos2d::Value;
class CsvData;
class CsvUtil : public Singleton<CsvUtil>
{
public:
	friend class Singleton<CsvUtil>;
	void loadFile(const char* sPath);
	CsvData* getCsv(const char* csvFilePath);
	Value getValue(int iRow, int iCol, const char* csvFilePath);
	const std::string get(int iRow, int iCol, const char* csvFilePath);
	const int getInt(int iRow, int iCol, const char* csvFilePath);
	const Size getFileRowColNum(const char* csvFilePath);
	const int findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath);
	std::vector<std::map<string, Value>> getDataFromCsv(const char* filepath);
private:
	Map<std::string, CsvData*> mCsvMap;
};

