#include "framework.h"
#include "Bro_Monster.h"

Bro_Monster::Bro_Monster()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(30);
	wstring path = (L"Monster/");
	_quad= make_shared<Quad>(path + L"Monster1.png");
	_quad->GetTransform()->GetScale().x *= 0.1f;
	_quad->GetTransform()->GetScale().y *= 0.1f;

	_quad->GetTransform()->SetParent(_transform);
	_collider->GetTransform()->SetParent(_transform);
	
	_transform->GetPos() = { CENTER_X, CENTER_Y + 200 };
}

Bro_Monster::~Bro_Monster()
{
}

void Bro_Monster::Update()
{	
	_transform->Update();	
	_collider->Update();
	_transform->GetPos() += _direction * _speed * DELTA_TIME;
	_quad->Update();
}

void Bro_Monster::Render()
{
	_quad->Render();
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
	if (distance > 0.5f)
	{
		_direction = direction.Normal();		
	}
}

void Bro_Monster::LeftRight(shared_ptr<Bro_Player> player)
{
	if (player->GetTransform()->GetWorldPos().x > _transform->GetWorldPos().x)
	{
		_quad->SetLeftRight_leftRightBuffer(0);
	}

	if (player->GetTransform()->GetWorldPos().x < _transform->GetWorldPos().x)
	{
		_quad->SetLeftRight_leftRightBuffer(1);
	}
}
