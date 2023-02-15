#pragma once
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

private:
	shared_ptr<Bro_BackGround>			_bg;
	shared_ptr<Bro_Player>				_player;
	vector<shared_ptr<Bro_Monster>>		_monsters;
//	shared_ptr<Bro_Monster> _monster;

};

