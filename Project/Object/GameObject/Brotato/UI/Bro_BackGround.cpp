#include "framework.h"
#include "Bro_BackGround.h"

Bro_BackGround::Bro_BackGround()
{
	wstring path = (L"BackGround/");
	_mainBg = make_shared<Quad>(path + L"Bro_Background.png");
	_mainBg->GetTransform()->GetScale().x += 2;
	_mainBg->GetTransform()->GetScale().y += 4;
	_mainBg->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };


	_mainBg->Update();
}

Bro_BackGround::~Bro_BackGround()
{
}

void Bro_BackGround::Update()
{
}

void Bro_BackGround::Render()
{
	_mainBg->Render();
}

Vector2 Bro_BackGround::Limit()
{
	Vector2 result;
	result.x = _mainBg->GetTransform()->GetPos().x - _mainBg->GetSize().x *0.5f;
	result.y = _mainBg->GetTransform()->GetPos().x + _mainBg->GetSize().x *0.5f;

	return result;
}


