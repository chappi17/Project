#pragma once
class Bro_Player_SMG
{
public:
	Bro_Player_SMG();
	~Bro_Player_SMG();

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Quad> GetQuad() { return _quad; }
	shared_ptr<Collider> GetCollider() { return _collider; }

	void Update();
	void Render();

	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }

	UINT DMG = 1;
private:
	bool _isActive = true;
	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;
};

