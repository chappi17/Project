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

	void SetUnlock_G(bool isUnlock);
	bool Unlock_Gun() { return Unlock_G; }

	void SetUnlock_R(bool isUnlock);
	bool Unlock_Rail() { return Unlock_R; }

	void SetUnlock_S(bool isUnlock);
	bool Unlock_SMG() { return Unlock_S; }

	int GetPoints() const { return _points; }
	int SetPoints(int points) { return _points = points; }
	void AddPoints(int points) { _points += points; }

	bool GetStage0() { return Stage0; }
	void SetStage(bool first);
	
private:
	static SceneManager* _instance;

	unordered_map<string, shared_ptr<Scene>> _sceneTable;
	weak_ptr<Scene> _curScene;

	bool Stage0 = false;

	bool Unlock_R = false;
	bool Unlock_S = false;
	bool Unlock_G = false;
	
	int _points = 0;
};

