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


	void Reset();

	void ChangeScene();
	void FirstScene();
	void End_Stage();

	void Text();

	shared_ptr<Bro_Player> GetPlayer() { return _player; }

	bool stage0 = false;


private:
	shared_ptr<Transform> _camera;

	shared_ptr<Bro_BackGround>			_bg;
	shared_ptr<Bro_Player>				_player;
	shared_ptr<HPBar> _bar;
	shared_ptr<First_Scene> _first;


	shared_ptr<Monster_manager>			_monster_manager;
	shared_ptr<Bro_Monster>				_bromonster;

	float _spawnTimer = 0;

	int _countStage = 1;

	double TimeSet = 0.0f;
	double TimeSet_res = 0.0f;
//	shared_ptr<Bro_Monster> _monster;

};

