#pragma once
class Monster_manager
{
public:

	Monster_manager();
	~Monster_manager();

	void CreateMonsters();
	void CreateBoss();

	void LeftRight(shared_ptr<Bro_Player> player);

	void Update();
	void Render();

	vector<shared_ptr<Bro_Monster>>		_monsters;
	vector<shared_ptr<Bro_Boss>>		 _boss;

	int respown = 10;

private:
	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transform;
};

