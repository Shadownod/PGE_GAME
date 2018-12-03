#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include "cocos2d.h"
#include <string>

using std::string;

USING_NS_CC;



class SceneManager
{
	static SceneManager *instance;
	SceneManager();

public:
	~SceneManager();

	Map<string, cocos2d::Scene*> SceneMap;


	static SceneManager* Instance()
	{
		if (!instance)
			instance = new SceneManager();
		return instance;
	}

	void RegisterScene(string SceneName, cocos2d::Scene* Scene);

	bool SceneExist(string &SceneName);

	cocos2d::Scene* GetScene(string SceneName);


	void runScene(string SceneName);


};




#endif
