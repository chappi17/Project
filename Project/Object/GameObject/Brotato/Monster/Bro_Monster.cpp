#include "framework.h"
#include "Bro_Monster.h"


Bro_Monster::Bro_Monster()
{
	CreateMonsters();
	_quad->GetTransform()->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetParent(_transform);
}

Bro_Monster::~Bro_Monster()
{
}

void Bro_Monster::Update()
{
	Idle();
	if (!isActive) return;

	_quad->Update();
	_transform->Update();
	_transform->GetPos() += _direction * _speed * DELTA_TIME;	
	_collider->Update();
}

void Bro_Monster::Render()
{
	if (!isActive) return;
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

	if (_collider->IsCollision(player->GetCollider()))
	{
		player->isActive = false;
	}
}

void Bro_Monster::LeftRight(shared_ptr<Bro_Player> player)
{
	if (player->GetTransform()->GetWorldPos().x > _quad->GetTransform()->GetWorldPos().x)
	{
		_quad->SetLeftRight_leftRightBuffer(0);
	}

	if (player->GetTransform()->GetWorldPos().x < _quad->GetTransform()->GetWorldPos().x)
	{
		_quad->SetLeftRight_leftRightBuffer(1);
	}
}

void Bro_Monster::CreateMonsters()
{
		wstring path = (L"Monster/");
		_quad = make_shared<Quad>(path + L"Monster1.png");
		_quad->GetTransform()->GetScale().x *= 0.1f;
		_quad->GetTransform()->GetScale().y *= 0.1f;

		_transform = make_shared<Transform>();
		_collider = make_shared<CircleCollider>(15);		
	
		float RespawnX = rand() % ((WIN_WIDTH + 100) - (-100) + 1) + (-100);
		float RespawnY = rand() % ((WIN_HEIGHT + 260) - (-260) + 1) + (-260);
		_transform->GetPos() = {RespawnX,RespawnY};
}

void Bro_Monster::Respawn()
{
	isActive = true;
}

void Bro_Monster::Idle()
{
	float offset = rand() % 360;
	float stretchAmount = 0.05f * sin(2.0f * (DELTA_TIME ) * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.07f)
	{
		_quad->GetTransform()->GetScale().y = 0.1f;
	}
}

bool Bro_Monster::IsCollision(shared_ptr<Collider> _col)
{
	if (isActive == false)
		return false;

	return _collider->IsCollision(_col);
}


