#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BagicScene/CupHeadScene.h"
#include "../Scene/BagicScene/FilterScene.h"
#include "../Scene/BagicScene/EffectScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	shared_ptr<Scene> cupScene = make_shared<CupHeadScene>();
	_sceneTable["CupHead"] = cupScene;

	shared_ptr<Scene> filterScene = make_shared<FilterScene>();
	_sceneTable["Filter"] = filterScene;

	shared_ptr<Scene> effectScene = make_shared<EffectScene>();
	_sceneTable["Effect"] = effectScene;

	_curScene = cupScene;
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
