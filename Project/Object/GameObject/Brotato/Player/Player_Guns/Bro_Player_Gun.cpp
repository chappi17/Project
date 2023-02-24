#include "framework.h"
#include "Bro_Player_Gun.h"

Bro_Player_Gun::Bro_Player_Gun()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(Vector2(35.0f, 10.0f));

	wstring path = (L"Gun/");
	_quad = make_shared<Quad>(path + L"gun.png");
	_quad->GetTransform()->GetScale().x *= 0.05f;
	_quad->GetTransform()->GetScale().y *= 0.05f;

	_quad->GetTransform()->SetParent(_transform);
	_collider->GetTransform()->SetParent(_transform);

}

Bro_Player_Gun::~Bro_Player_Gun()
{
}

void Bro_Player_Gun::Update()
{
	if (IsActive() == false)
		return;

	_transform->Update();
	_collider->Update();
	_quad->Update();
}

void Bro_Player_Gun::Render()
{
	if (IsActive() == false)
		return;

	_collider->Render();
	_quad->Render();
}

void Bro_Player_Gun::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;
}


