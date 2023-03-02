#include "framework.h"
#include "Bro_Monster.h"

Bro_Monster::Bro_Monster()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(25);
	CreateMonsters();
	_quad->GetTransform()->SetParent(_collider->GetTransform());
	_collider->GetTransform()->SetParent(_transform);
}

Bro_Monster::~Bro_Monster()
{
}

void Bro_Monster::Update()
{
	if (_isActive==false) 
		return;	
	_transform->GetPos() += _direction * _speed * DELTA_TIME;
	_transform->Update();
	_collider->Update();
	_quad->Update();

	Idle();
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
		if (_delaytime  > 1.0f)
		{
			_damagedelay = false;
			_delaytime = 0.0f;
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
	if (_isActive == false)
		return;

	//float offset = rand() % 360;
	float stretchAmount = 0.05f * sin(2.0f * (DELTA_TIME) * 0.3f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.07f)
	{
		_quad->GetTransform()->GetScale().y = 0.1f;
	}
}

void Bro_Monster::Init()
{

}

void Bro_Monster::Dead()
{	
}

void Bro_Monster::Die()
{
	Dead();
	SetActive(false);
}


void Bro_Monster::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;
}