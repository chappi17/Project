#include "framework.h"
#include "Bro_Player.h"

Bro_Player::Bro_Player()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(25);
	wstring path = (L"Player/");
	_player = make_shared<Quad>(path + L"Player.png");
	_player->GetTransform()->GetScale().x *= 0.25f;
	_player->GetTransform()->GetScale().y *= 0.25f;	

	_collider->GetTransform()->SetParent(_transform);
	_player->GetTransform()->SetParent(_transform);

	_transform->GetPos() = { CENTER_X, CENTER_Y};

}

Bro_Player::~Bro_Player()
{
}

void Bro_Player::Update()
{
	Input();
	_transform->Update();
	_player->Update();
	_collider->Update();
}

void Bro_Player::Render()
{
	_player->Render();
	_collider->Render();
}

void Bro_Player::Input()
{
	if (KEY_PRESS('A') && (_transform->GetPos().x >-100))
	{
		_transform->GetPos().x -= DELTA_TIME * _speed;
		_player->SetLeftRight_leftRightBuffer(1);
	}

	if (KEY_PRESS('D') && (_transform->GetPos().x < 1380))
	{
		_transform->GetPos().x += DELTA_TIME * _speed;
		_player->SetLeftRight_leftRightBuffer(0);
	}

	if (KEY_PRESS('W') && (_transform->GetPos().y < 980))
	{
		_transform->GetPos().y += DELTA_TIME * _speed;
	}

	if (KEY_PRESS('S') && (_transform->GetPos().y > -260))
	{
		_transform->GetPos().y -= DELTA_TIME * _speed;
	}
}
