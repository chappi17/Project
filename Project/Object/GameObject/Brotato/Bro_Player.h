#pragma once
class Bro_Player
{
public:
	Bro_Player();
	~Bro_Player();

	void Update();
	void Render();

	void Input();

	void SetLeft() { _leftright->_data.leftRight = 1; }
	void SetRight() { _leftright->_data.leftRight = 0; }

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _player;
	float _speed = 250.0f;

	shared_ptr<LeftRightBuffer> _leftright;

};

