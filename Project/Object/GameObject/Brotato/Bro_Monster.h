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

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _monster;	

	shared_ptr<LeftRightBuffer> _leftright;

	Vector2 _direction = { 0,0 };
	float _speed = 100.0f;

};

