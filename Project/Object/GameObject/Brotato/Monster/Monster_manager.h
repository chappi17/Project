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


	vector<InstanceData> _instanceDataes;  // ���� ��ġ ������ �� �׸��� �нż� �ϴ°�
	shared_ptr<VertexBuffer> _instanceBuffer;
};

