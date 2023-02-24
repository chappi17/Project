#include "framework.h"
#include "Bro_Player_Bullet_SMG.h"

Bro_Player_Bullet_SMG::Bro_Player_Bullet_SMG()
{
	_transform = make_shared<Transform>();
	wstring path = (L"Effect/");
	_quad = make_shared<Quad>(path + L"Bullet.png", Vector2{ 60,60 });
	_collider = make_shared<CircleCollider>(10);
	_collider->GetTransform()->GetPos().x = 10;
	_collider->GetTransform()->GetPos().y = -2;

	_quad->GetTransform()->SetParent(_transform);
	_collider->GetTransform()->SetParent(_transform);
}

Bro_Player_Bullet_SMG::~Bro_Player_Bullet_SMG()
{
}

void Bro_Player_Bullet_SMG::Update()
{
	if (IsActive() == false)
		return;

	_transform->GetPos() += _direction * _speed * DELTA_TIME;
	_transform->Update();
	_collider->Update();
	_quad->Update();
}

void Bro_Player_Bullet_SMG::Render()
{
	if (IsActive() == false)
		return;

	_quad->Render();
	_collider->Render();
}

void Bro_Player_Bullet_SMG::SetDirection(Vector2 dir)
{
	_direction = dir;
}

void Bro_Player_Bullet_SMG::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;

	_transform->SetSRT();
	_collider->GetTransform()->SetSRT();
	_quad->GetTransform()->SetSRT();
}
