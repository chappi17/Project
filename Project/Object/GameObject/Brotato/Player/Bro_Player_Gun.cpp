#include "framework.h"
#include "Bro_Player_Gun.h"

Bro_Player_Gun::Bro_Player_Gun()
{
	_transform = make_shared<Transform>();
	wstring path = (L"Gun/");
	_quad = make_shared<Quad>(path + L"gun.png");
	_quad->GetTransform()->GetScale().x *= 0.05f;
	_quad->GetTransform()->GetScale().y *= 0.05f;

	_quad->GetTransform()->SetParent(_transform);

	//_transform->GetPos() = { CENTER_X,CENTER_Y };
}

Bro_Player_Gun::~Bro_Player_Gun()
{
}

void Bro_Player_Gun::Update()
{
	_transform->Update();
	_quad->Update();
}

void Bro_Player_Gun::Render()
{
	_quad->Render();
}
