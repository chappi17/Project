#include "framework.h"
#include "SceneManager.h"

#include "../Scene/Brotato/BrotatoScene.h"
#include "../Scene/Brotato/Brotato_Store.h"
#include "../Scene/Brotato/Instancing_Test.h"
#include "../Scene/Brotato/First_Scene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	shared_ptr<Scene> broScene = make_shared<BrotatoScene>();
	_sceneTable["BroScene"] = broScene;

	shared_ptr<Scene> brostoreScene = make_shared<Brotato_Store>();
	_sceneTable["Brotato_Store"] = brostoreScene;

	shared_ptr<Scene> Instancing = make_shared<Instancing_Test>();
	_sceneTable["Instancing"] = Instancing;

	shared_ptr<Scene> First = make_shared<First_Scene>();
	_sceneTable["First"] = First;

	_curScene = First;
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

void SceneManager::SetUnlock_G(bool isUnlock)
{
	Unlock_G = isUnlock;
}

void SceneManager::SetUnlock_R(bool isUnlock)
{
	Unlock_R = isUnlock;
}

void SceneManager::SetUnlock_S(bool isUnlock)
{
	Unlock_S = isUnlock;
}

void SceneManager::SetStage(bool first)
{
	Stage0 = first;
}
