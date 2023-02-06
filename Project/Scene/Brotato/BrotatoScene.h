#pragma once
class BrotatoScene : public Scene
{
public:
	BrotatoScene();
	~BrotatoScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:

	shared_ptr<Bro_BackGround>	_bg;
	shared_ptr<Bro_Player>		_player;
	vector<shared_ptr<Bro_Monster>>		_monsters;
	shared_ptr<Bro_Monster> _monster;
};

