#include "framework.h"
#include "Bro_Monster.h"

Bro_Monster::Bro_Monster()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(30);
	wstring path = (L"Monster/");
	_monster= make_shared<Quad>(path + L"Monster1.png");
	_monster->GetTransform()->GetScale().x *= 0.1f;
	_monster->GetTransform()->GetScale().y *= 0.1f;

	_collider->GetTransform()->SetParent(_transform);
	_monster->GetTransform()->SetParent(_transform);

	_transform->GetPos() = { CENTER_X, CENTER_Y + 100 };
}

Bro_Monster::~Bro_Monster()
{
}

void Bro_Monster::Update()
{	
	_transform->Update();	
	_collider->Update();
	_monster->GetTransform()->GetPos() += _direction * _speed * DELTA_TIME;
	_monster->Update();
}

void Bro_Monster::Render()
{
	_monster->Render();
	_collider->Render();
}

void Bro_Monster::SetDirection(Vector2 dir)
{
	float angle = dir.Angle();
	_direction = dir;
}

void Bro_Monster::Attack(shared_ptr<Bro_Player> player)
{
	Vector2 direction = player->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
	float distance = direction.Length();
	if (distance > 50.0f)
	{
		_direction = direction.Normal();
	}
}
