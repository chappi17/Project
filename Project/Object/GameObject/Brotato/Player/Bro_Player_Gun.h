#pragma once
class Bro_Player_Gun
{
public:
	Bro_Player_Gun();
	~Bro_Player_Gun();

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Quad> GetQuad() { return _quad; }

	void Update();
	void Render();

private:

	shared_ptr<Collider> _collider;
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;
};

