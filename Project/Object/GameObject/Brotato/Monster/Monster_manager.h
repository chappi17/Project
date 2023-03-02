#pragma once
class Monster_manager
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
	};


	Monster_manager();
	~Monster_manager();

	void CreateMonsters();

	void LeftRight(shared_ptr<Bro_Player> player);

	void Update();
	void Render();

	vector<shared_ptr<Bro_Monster>>		_monsters;

private:
	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transform;


	vector<InstanceData> _instanceDataes;  // 생성 위치 모조리 찍어서 그림자 분신술 하는거
	shared_ptr<VertexBuffer> _instanceBuffer;
};

