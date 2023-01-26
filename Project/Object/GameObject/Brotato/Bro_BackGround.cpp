#include "framework.h"
#include "Bro_BackGround.h"

Bro_BackGround::Bro_BackGround()
{
	wstring path = (L"BackGround/");
	_mainBg = make_shared<Quad>(path + L"Bro_Background.png");
	_mainBg->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
	_mainBg->GetTransform()->GetScale().x += 2;
	_mainBg->GetTransform()->GetScale().y += 2;


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

Vector2 Bro_BackGround::GetSize()
{
	Vector2 result = _mainBg->GetSize();
	return result;
}
