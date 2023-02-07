#include "framework.h"
#include "Bro_Player.h"

Bro_Player::Bro_Player()
{
	_transform = make_shared<Transform>();	
	_collider = make_shared<CircleCollider>(25);

	_transform->GetPos() = { CENTER_X, CENTER_Y};

	wstring path = (L"Player/");
	_quad = make_shared<Quad>(path + L"Player.png");
	_gun = make_shared<Bro_Player_Gun>();
	_gun->GetTransform()->GetPos().x = 35;

	_quad->GetTransform()->GetScale().x *= 0.25f;
	_quad->GetTransform()->GetScale().y *= 0.25f;

	_gun->GetTransform()->SetParent(_transform);
	_collider->GetTransform()->SetParent(_transform);
	_quad->GetTransform()->SetParent(_transform);
	
}

Bro_Player::~Bro_Player()
{
}

void Bro_Player::Update()
{
	if (isActive == false)
		return;

	Input();
	Idle();

	_transform->Update();


	_quad->Update();
	_gun->Update();
	_collider->Update();

}

void Bro_Player::Render()
{
	if (isActive == false)
		return;

	_quad->Render();

	_gun->Render();
	_collider->Render();
}

void Bro_Player::Input()
{
	if (KEY_PRESS('A') && (_transform->GetPos().x >-100))
	{
		_transform->GetPos().x -= DELTA_TIME * _speed;
		_quad->SetLeftRight_leftRightBuffer(1);
		float newX = _transform->GetPos().x;
		_gun->GetTransform()->GetPos().x = min(newX, -40);
		_gun->GetQuad()->SetLeftRight_leftRightBuffer(1);
		Moving();
	}

	if (KEY_PRESS('D') && (_transform->GetPos().x < 1380))
	{
		_transform->GetPos().x += DELTA_TIME * _speed;
		_quad->SetLeftRight_leftRightBuffer(0);
		float newX = _transform->GetPos().x;
		_gun->GetTransform()->GetPos().x = min(newX, 40);
		_gun->GetQuad()->SetLeftRight_leftRightBuffer(0);

		Moving();
	}

	if (KEY_PRESS('W') && (_transform->GetPos().y < 980))
	{
		_transform->GetPos().y += DELTA_TIME * _speed;
		Moving();
	}

	if (KEY_PRESS('S') && (_transform->GetPos().y > -260))
	{
		_transform->GetPos().y -= DELTA_TIME * _speed;
		Moving();
	}
}

void Bro_Player::Idle()
{
	float stretchAmount = 0.05f * sin(2.0f * DELTA_TIME * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.19f)
	{
		_quad->GetTransform()->GetScale().y = 0.25f;
	}
}

void Bro_Player::Moving()
{
	float stretchAmount = 0.05f * sin(2.0f * DELTA_TIME * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.21f)
	{
		_quad->GetTransform()->GetScale().y = 0.25f;
	}
}

void Bro_Player::Fire()
{

}
