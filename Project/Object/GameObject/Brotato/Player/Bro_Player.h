#pragma once
class Bro_Monster;
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
	void Idle();
	void Moving();



	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetCollider() { return _collider; }

	shared_ptr<Bro_Player_Gun> GetGun() { return _gun; }
	shared_ptr<Bro_Player_RailGun> GetRailGun() { return _railgun; }
	shared_ptr<Bro_Player_SMG> GetSMG() { return _smg; }

	shared_ptr<Bro_Player_Bullet> GetBullet() { return _bullet; }
	shared_ptr<Collider> GetRadius() { return _radious; }
	UINT& GetHp() { return _Hp; }


	void SetLimit(Vector2 bg) { _bg = bg; }

	void Attack(vector<shared_ptr<Bro_Monster>>& monsters);

	void Target(vector<shared_ptr<Bro_Monster>>& monsters);

	void Shot();
	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }
	bool _damageDelay = false;

private:

	bool _isActive = true;
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;

	shared_ptr<Bro_Player_Gun> _gun;
	shared_ptr<Bro_Player_RailGun>	_railgun;
	shared_ptr<Bro_Player_SMG> _smg;


	shared_ptr<Transform> _firePos;
	shared_ptr<class Bro_Player_Bullet > _bullet;
	shared_ptr<Bro_Monster> _target;
	//	vector< shared_ptr<class Bro_Player_Bullet>> _bullets;

	shared_ptr<Collider> _radious;

	shared_ptr<Quad> _quad;
	float _speed = 250.0f;

	float _check = 0.0f;
	float _delay = 1.0f;

	shared_ptr<LeftRightBuffer> _leftright;
	Vector2 _limitMove;
	Vector2 _bg;


	UINT _Hp = 12;
};

