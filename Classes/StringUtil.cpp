#include "StringUtil.h"

ValueVector StringUtil::split(const char* srcStr, const char* sSep)
{
	ValueVector stringList;
	int size = strlen(srcStr);
	Value str = Value(srcStr);
	int startIndex = 0;
	int endIndex = 0;
	endIndex = str.asString().find(sSep);
	std::string lineStr;
	while (endIndex > 0)
	{
		lineStr = str.asString().substr(startIndex, endIndex);
		stringList.push_back(Value(lineStr));
		str = Value(str.asString().substr(endIndex + 1, size));
		endIndex = str.asString().find(sSep);
	}
	if (!str.asString().empty())
	{
		stringList.push_back(Value(str.asString()));
	}
	return stringList;
}
