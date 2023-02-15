#pragma once
class Bro_Resource
{
public:
	Bro_Resource();
	~Bro_Resource();

	void Update();
	void Render();

	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }

	shared_ptr<Quad> GetQuad() {return _quad;}

private:
	bool _isActive = false;
	shared_ptr<Quad> _quad;
};

