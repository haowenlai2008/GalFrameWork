#pragma once
#include "cocos2d.h"
#include <map>;
using std::map;
using std::shared_ptr;
class SceneData;
class DataManager
{
public:
	static DataManager* getInstance();
	void init();
	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;
	SceneData& getSceneData(int sceneID);
	CC_SYNTHESIZE(int, currentSceneID, CurrentScene);
private:
	static DataManager* p_dm;
	map<int, shared_ptr<SceneData>> sceneData;
	DataManager() {};
};

