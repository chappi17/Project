#pragma once
class Store_menu;
class BrotatoScene : public Scene
{
public:
	BrotatoScene();
	~BrotatoScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateMonsters();
	void Reset();

	void ChangeScene();
	void End_Stage();

	void Init();
	
	int _currentMonster = 0;


	shared_ptr<Bro_Player> GetPlayer() { return _player; }

private:
	shared_ptr<Transform> _camera;

	shared_ptr<Bro_BackGround>			_bg;
	shared_ptr<Bro_Player>				_player;
	vector<shared_ptr<Bro_Monster>>		_monsters;
	shared_ptr<Bro_Resource>			_resource;

	float _spawnTimer = 0;

	bool Stage0 = true;

	double TimeSet = 0.0f;
	double TimeSet_res = 0.0f;

//	shared_ptr<Bro_Monster> _monster;

};

