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
	void Respawn();

	void Idle();

	bool IsCollision(shared_ptr<Collider> _col);

	shared_ptr<Collider> GetCollider() { return _collider; }

	bool isActive = false;

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;	

	vector<shared_ptr<Quad>> _quads;

	shared_ptr<LeftRightBuffer> _leftright;

	Vector2 _direction = { 0,0 };
	float _speed = 100.0f;

};

