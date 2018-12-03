#include "SceneManager.h"
#include "HelloWorldScene.h"
#include "GoodBye.h"
#include "LoadScreen.h"

SceneManager* SceneManager::instance = 0;
SceneManager::SceneManager()
{
	RegisterScene("LoadScreen", LoadScreen::createScene());
	RegisterScene("GoodBye", GoodBye::createScene());
	RegisterScene("HelloWorld", HelloWorld::createScene());
	

}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterScene(string SceneName, cocos2d::Scene * Scene)
{
	if (SceneExist(SceneName))
		return;

	Scene->init();
	SceneMap.insert(SceneName, Scene);
}

bool SceneManager::SceneExist(string & SceneName)
{
	Map<string, cocos2d::Scene*>::iterator it = SceneMap.find(SceneName);

	if (it != SceneMap.end())
	{
		return true;
	}

	return false;

}

cocos2d::Scene * SceneManager::GetScene(string SceneName)
{
	return SceneMap.at(SceneName);
}

void SceneManager::runScene(string SceneName)
{
	if (!SceneExist(SceneName))
		return;

	//GetScene(SceneName)->create();

	CCDirector::getInstance()->replaceScene(GetScene(SceneName));
}
