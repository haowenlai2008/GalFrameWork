#include "DataManager.h"
DataManager* DataManager::p_dm = nullptr;
DataManager* DataManager::getInstance()
{
	if (p_dm == nullptr)
		p_dm = new (std::nothrow)DataManager();
	return p_dm;
}

SceneData& DataManager::getSceneData(int sceneID)
{
	return *sceneData[sceneID];
}
