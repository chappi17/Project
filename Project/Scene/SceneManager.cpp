#include "framework.h"
#include "SceneManager.h"

#include "../Scene/Brotato/BrotatoScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	shared_ptr<Scene> broScene = make_shared<BrotatoScene>();
	_sceneTable["BroScene"] = broScene;

	_curScene = broScene;
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
