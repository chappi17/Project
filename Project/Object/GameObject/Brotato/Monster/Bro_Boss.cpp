#include "framework.h"
#include "Bro_Boss.h"

Bro_Boss::Bro_Boss()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(25);
	CreateMonsters();
	_quad->GetTransform()->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetParent(_transform);
}

Bro_Boss::~Bro_Boss()
{
	if (_isActive == false)
		return;
	_transform->GetPos() += _direction * _speed * DELTA_TIME;
	_transform->Update();
	_collider->Update();
	_quad->Update();

	Idle();
}

void Bro_Boss::Update()
{
	_transform->Update();
	_collider->Update();
	_quad->Update();
}

void Bro_Boss::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_collider->Render();
}

void Bro_Boss::SetDirection(Vector2 dir)
{
	float angle = dir.Angle();
	_direction = dir;
}

void Bro_Boss::Attack(shared_ptr<Bro_Player> player)
{
	Vector2 direction = player->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
	float distance = direction.Length();
	if (distance > 0.5f)
	{
		_direction = direction.Normal();
	}

	// 이동 제한
	_transform->GetPos().x < 1380 || _transform->GetPos().x > -100 ||
		_transform->GetPos().y < 980 || _transform->GetPos().y > -260;


	if (_damagedelay == false)
	{
		if (_collider->IsCollision(player->GetCollider()))
		{
			player->GetHp() -= DMG;
			CAMERA->ShakeStart(3.0f, 0.3f);
			_damagedelay = true;
		}
	}
	else
		_delaytime += DELTA_TIME;
	if (_delaytime > 1.0f)
	{
		_damagedelay = false;
		_delaytime = 0.0f;
	}
}

void Bro_Boss::LeftRight(shared_ptr<Bro_Player> player)
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

void Bro_Boss::CreateMonsters()
{
	wstring path = (L"Monster/");
	_quad = make_shared<Quad>(path + L"Monster2.png");
	_quad->GetTransform()->GetScale().x *= 0.1f;
	_quad->GetTransform()->GetScale().y *= 0.1f;
}

void Bro_Boss::Idle()
{
	if (_isActive == false)
		return;

	//float offset = rand() % 360;
	float stretchAmount = 0.05f * sin(2.0f * (DELTA_TIME) * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.07f)
	{
		_quad->GetTransform()->GetScale().y = 0.1f;
	}
}

void Bro_Boss::Init()
{
}

void Bro_Boss::Dead()
{
}

void Bro_Boss::Die()
{
	SetActive(false);
}

void Bro_Boss::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;
}
