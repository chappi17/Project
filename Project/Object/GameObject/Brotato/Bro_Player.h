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

	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetLimit(Vector2 bg) { _bg = bg; }

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _player;
	float _speed = 250.0f;

	shared_ptr<LeftRightBuffer> _leftright;

	Vector2 _limitMove;

	Vector2 _bg;
};

