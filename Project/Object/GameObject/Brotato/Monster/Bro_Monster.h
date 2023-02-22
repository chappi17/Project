#pragma once
class Bro_Monster
{
public:

	struct InstanceData
	{
		XMMATRIX matrix;
	};

	Bro_Monster();
	~Bro_Monster();

	void Update();
	void Render();

	void SetLeft() { _leftright->_data.leftRight = 1; }
	void SetRight() { _leftright->_data.leftRight = 0; }

	void SetDirection(Vector2 dir);

	void Attack(shared_ptr<Bro_Player> player);
	void LeftRight(shared_ptr<Bro_Player> player);

	void CreateMonsters();

	void Idle();
	void Init();
	void Dead();


	void Die();
	void OffSet();

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Quad> GetQuad() { return _quad; }
	float& GetHp() { return _Hp; }



	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }
	void SetEndEvent(CallBack function) { _endEvnet = function; }
	void Resource();

private:
	bool _isActive = false;
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _quad; // 그림 하나 그리고
	vector<InstanceData> _instanceDataes;  // 생성 위치 모조리 찍어서 그림자 분신술 하는거
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<LeftRightBuffer> _leftright;

	

	Vector2 _direction = { 0,0 };
	float _speed = 100.0f;

	bool _damagedelay = false;
	float _delaytime = 0.0f;

	CallBack _endEvnet = nullptr;

	float _Hp = 15.0f;
	float DMG = 1.0f;
};

