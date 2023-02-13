#pragma once
class Bro_Monster;
class Bro_Player_Gun
{
public:
	Bro_Player_Gun();
	~Bro_Player_Gun();

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Quad> GetQuad() { return _quad; }
	shared_ptr<Collider> GetCollider() { return _collider; }

	void Update();
	void Render();

	UINT DMG = 1;
private:
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;


	//vector<shared_ptr<class Bro_Player_Bullet>> _bullets;


};

