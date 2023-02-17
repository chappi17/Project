#pragma once
class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new SceneManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SceneManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Render();
	void PreRender();
	void PostRender();

	void ChangeScene(string name);

	void SetUnlock_R(bool isUnlock);
	bool Unlock_Rail() { return Unlock_R; }

	void SetUnlock_S(bool isUnlock);
	bool Unlock_SMG() { return Unlock_S; }


private:


	static SceneManager* _instance;

	unordered_map<string, shared_ptr<Scene>> _sceneTable;
	weak_ptr<Scene> _curScene;
	bool Unlock_R = false;
	bool Unlock_S = false;
};

