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
	void Dead();



	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetCollider() { return _collider; }

	shared_ptr<Bro_Player_Gun> GetGun() { return _gun; }
	shared_ptr<Bro_Player_RailGun> GetRailGun() { return _railgun; }
	shared_ptr<Bro_Player_SMG> GetSMG() { return _smg; }

	shared_ptr<Bro_Player_Bullet> GetBullet() { return _bullet; }
	shared_ptr<Collider> GetRadius() { return _radious; }
	float& GetHp() { return _Hp; }


	void SetLimit(Vector2 bg) { _bg = bg; }

	void Attack(vector<shared_ptr<Bro_Monster>>& monsters);
	void Attack_R(vector<shared_ptr<Bro_Monster>>& monsters);
	void Attack_SMG(vector<shared_ptr<Bro_Monster>>& monsters);

	void Target(vector<shared_ptr<Bro_Monster>>& monsters);
	void Target_R(vector<shared_ptr<Bro_Monster>>& monsters);
	void Target_SMG(vector<shared_ptr<Bro_Monster>>& monsters);

	void Shot();
	void Shot_R();
	void Shot_SMG();


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
	shared_ptr<Transform> _firePos_R;
	shared_ptr<Transform> _firePos_SMG;

	shared_ptr<class Bro_Player_Bullet > _bullet;
	shared_ptr<class Bro_player_Bullet_Rail> _railbullet;
	shared_ptr<class Bro_Player_Bullet_SMG> _smgbullet;


	shared_ptr<Bro_Monster> _target;
	//	vector< shared_ptr<class Bro_Player_Bullet>> _bullets;

	shared_ptr<Collider> _radious;
	shared_ptr<Collider> _radious_R;
	shared_ptr<Collider> _radious_SMG;

	shared_ptr<Quad> _quad;
	float _speed = 250.0f;

	shared_ptr<LeftRightBuffer> _leftright;
	Vector2 _limitMove;
	Vector2 _bg;

	

	float _Hp = 12.0f;

	const float _fireDelay = 1.0f;
	const float _fireDelay_R = 1.2f;
	const float _fireDelay_S = 0.1f;
	
	float _fireCheck = 0.0f;
	float _fireCheck_R = 0.0f;
	float _fireCheck_S = 0.0f;
};

