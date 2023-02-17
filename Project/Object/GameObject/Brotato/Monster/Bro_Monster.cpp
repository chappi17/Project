#include "framework.h"
#include "Bro_Monster.h"

Bro_Monster::Bro_Monster()
{
	CreateMonsters();
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(25);
	_quad->GetTransform()->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetParent(_transform);
	
}

Bro_Monster::~Bro_Monster()
{
}

void Bro_Monster::Update()
{
	if (_isActive == false)
		return;
	Idle();
	_quad->Update();
	_transform->Update();
	_transform->GetPos() += _direction * _speed * DELTA_TIME;
	_collider->Update();
}

void Bro_Monster::Render()
{
	if (_isActive == false)
		return;

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
		if (!player->_damageDelay)
		{
			--player->GetHp();
			CAMERA->ShakeStart(3.0f, 0.3f);
			player->_damageDelay = true;
			if (Timer::GetInstance()->GetElasedTime() < 2.0f)
			{
				player->_damageDelay = false;
			}
		}		
		if (player->GetHp() <= 0)
		{
			player->SetActive(false);
			player->Update();
		}
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
}


void Bro_Monster::Idle()
{
	float offset = rand() % 360;
	float stretchAmount = 0.05f * sin(2.0f * (DELTA_TIME) * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.07f)
	{
		_quad->GetTransform()->GetScale().y = 0.1f;
	}
}

void Bro_Monster::Init()
{
}

void Bro_Monster::Die()
{
	SetActive(false);
	//Resource();
}

void Bro_Monster::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;
}

void Bro_Monster::Resource()
{
	_resource->SetActive(true);
	_resource->GetQuad()->GetTransform()->GetPos() = this->GetTransform()->GetWorldPos();
}