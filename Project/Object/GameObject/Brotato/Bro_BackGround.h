#pragma once
class Bro_BackGround
{
public:
	Bro_BackGround();
	~Bro_BackGround();

	void Update();
	void Render();

	Vector2 GetSize();

private:

	shared_ptr<Quad>	_mainBg;
};