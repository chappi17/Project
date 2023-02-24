#pragma once
class Bro_player_Bullet_Rail
{
public:
	Bro_player_Bullet_Rail();
	~Bro_player_Bullet_Rail();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Quad> GetQuad() { return _quad; }


	//void Attack(vector<shared_ptr<Bro_Monster>>& monsters);

	void SetDirection(Vector2 dir);
	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }

private:
	bool _isActive = false;

	shared_ptr<Transform>	_transform;
	shared_ptr<Quad>		_quad;
	shared_ptr <Collider>	_collider;
	shared_ptr<class Bro_Monster> _monster;

	Vector2 _direction = { 0,0 };
	Vector2 _firedirection = { 0,0 };

	float		_speed = 600.0f;
};

