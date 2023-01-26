#include "framework.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	//shared_ptr<Scene> cupScene = make_shared<CupHeadScene>();
	//_sceneTable["CupHead"] = cupScene;

	/*_curScene = cupScene;*/
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	if (_curScene.expired() == false)
		_curScene.lock()->Update();
}

void SceneManager::Render()
{
	if (_curScene.expired() == false)
		_curScene.lock()->Render();
}

void SceneManager::PreRender()
{
	if (_curScene.expired() == false)
		_curScene.lock()->PreRender();
}

void SceneManager::PostRender()
{
	if (_curScene.expired() == false)
		_curScene.lock()->PostRender();
}

void SceneManager::ChangeScene(string name)
{
	_curScene = _sceneTable[name];
}
