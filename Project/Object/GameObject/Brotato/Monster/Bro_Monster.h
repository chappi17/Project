#pragma once
class Bro_Monster
{
public:
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
	void Die();


	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Quad> GetQuad() { return _quad; }
	UINT& GetHp() { return _Hp; }



	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }
	void SetEndEvent(CallBack function) { _endEvnet = function; }
	void Resource();

private:
	bool _isActive = false;
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;

	vector<shared_ptr<Quad>> _quads;

	shared_ptr<LeftRightBuffer> _leftright;

	shared_ptr<Bro_Resource> _resource;

	Vector2 _direction = { 0,0 };
	float _speed = 100.0f;

	CallBack _endEvnet = nullptr;

	UINT _Hp = 15;
};

