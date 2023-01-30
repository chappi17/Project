#pragma once
class Bro_BackGround
{
public:
	Bro_BackGround();
	~Bro_BackGround();

	void Update();
	void Render();

	Vector2 GetSize() { return _mainBg->GetSize(); }
	Vector2 GetMainPos() { return _mainBg->GetTransform()->GetWorldPos(); }

	Vector2 Limit();

	

private:
	shared_ptr<Quad>	_mainBg;
};