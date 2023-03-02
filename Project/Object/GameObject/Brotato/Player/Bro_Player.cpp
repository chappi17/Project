#include "framework.h"
#include "Bro_Player.h"

Bro_Player::Bro_Player()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(25);

	_radious = make_shared<CircleCollider>(300);
	_radious_R = make_shared<CircleCollider>(380);
	_radious_SMG = make_shared<CircleCollider>(290);
		
	_firePos = make_shared<Transform>();
	_firePos_R = make_shared<Transform>();
	_firePos_SMG = make_shared<Transform>();

	_transform->GetPos() = { CENTER_X, CENTER_Y };

	wstring path = (L"Player/");
	_gun = make_shared<Bro_Player_Gun>();
	_railgun = make_shared<Bro_Player_RailGun>();
	_smg = make_shared<Bro_Player_SMG>();	

	_gun->GetTransform()->GetPos().x = +40;
	_smg->GetTransform()->GetPos().x = -40;
	_railgun->GetTransform()->GetPos().y = +40;
	
	//_railgun->SetActive(true);
	//_smg->SetActive(true);

	_quad = make_shared<Quad>(path + L"Player_1.png");
	_quad->GetTransform()->GetScale().x *= 1.0f;
	_quad->GetTransform()->GetScale().y *= 1.0f;

	_gun->GetTransform()->SetParent(_transform);
	_railgun->GetTransform()->SetParent(_transform);
	_smg->GetTransform()->SetParent(_transform);

	_collider->GetTransform()->SetParent(_transform);
	_quad->GetTransform()->SetParent(_transform);
	_radious->GetTransform()->SetParent(_transform);
	_radious_R->GetTransform()->SetParent(_transform);
	_radious_SMG->GetTransform()->SetParent(_transform);

	_firePos->SetParent(_gun->GetTransform());
	_firePos_R->SetParent(_railgun->GetTransform());
	_firePos_SMG->SetParent(_smg->GetTransform());	


	for (int i = 0; i < 5; i++)
	{
		auto bullet = make_shared<Bro_Player_Bullet>();
		bullet->SetActive(false);
		_bullet.push_back(bullet);
	}

	for (int i = 0; i < 5; i++)
	{
		auto smgbullet = make_shared<Bro_Player_Bullet_SMG>();
		_smgbullet.push_back(smgbullet);
	}

	for (int i = 0; i < 5; i++)
	{
		auto railbullet = make_shared<Bro_player_Bullet_Rail>();
		_railbullet.push_back(railbullet);
	}

	SOUND->Add("Shot", "Resource/Brotato/Sound/Gun.wav");
	SOUND->Add("Shot_R", "Resource/Brotato/Sound/RailGun.wav");
	SOUND->Add("Shot_SMG", "Resource/Brotato/Sound/SMG.wav");
	SOUND->Add("Hit_Sound", "Resource/Brotato/Sound/Hit_Sound.wav");
}

Bro_Player::~Bro_Player()
{
}

void Bro_Player::Update()
{
	if (_isActive == false)
		return;

	_fireCheck += DELTA_TIME;
	_fireCheck_R += DELTA_TIME;
	_fireCheck_S += DELTA_TIME;
	
	Input();
	Idle();
	_transform->Update();
	_quad->Update();
	_collider->Update();

	_gun->Update();
	_railgun->Update();
	_smg->Update();

	_radious->Update();
	_radious_R->Update();
	_radious_SMG->Update();

	_firePos->Update();
	_firePos_R->Update();
	_firePos_SMG->Update();

	for (auto bullet : _bullet)
	{
		bullet->Update();
	}

	for (auto smgbullet : _smgbullet)
	{
		smgbullet->Update();
	}

	for (auto railbullet : _railbullet)
	{
		railbullet->Update();
	}	
}

void Bro_Player::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_collider->Render();

	_gun->Render();
	_railgun->Render();
	_smg->Render();

	_radious->Render();
	_radious_R->Render();
	_radious_SMG->Render();

	for (auto bullet : _bullet)
	{
		bullet->Render();
	}

	for (auto railbullet : _railbullet)
	{
		railbullet->Render();
	}

	for (auto smgbullet : _smgbullet)
	{
		smgbullet->Render();
	}
}

void Bro_Player::Input()
{

	if (KEY_PRESS('A') && (_transform->GetPos().x > -100))
	{
		_transform->GetPos().x -= DELTA_TIME * _speed;
		_quad->SetLeftRight_leftRightBuffer(1);

	}

	if (KEY_PRESS('D') && (_transform->GetPos().x < 1380))
	{
		_transform->GetPos().x += DELTA_TIME * _speed;
		_quad->SetLeftRight_leftRightBuffer(0);

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

void Bro_Player::Idle()
{
	float stretchAmount = 0.5f * sin(2.0f * DELTA_TIME * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;

	if (_quad->GetTransform()->GetScale().y < 0.75f)
	{
		_quad->GetTransform()->GetScale().y = 1.0f;
	}
}

//void Bro_Player::Moving()
//{
//	float stretchAmount = 0.05f * sin(2.0f * DELTA_TIME * 0.5f);
//	_quad->GetTransform()->GetScale().y -= stretchAmount;
//
//	if (_quad->GetTransform()->GetScale().y < 0.21f)
//	{
//		_quad->GetTransform()->GetScale().y = 1.0f;
//	}
//}

void Bro_Player::Dead()
{
	float stretchAmount = 0.05f * sin(2.0f * DELTA_TIME * 0.5f);
	_quad->GetTransform()->GetScale().y -= stretchAmount;
//	_quad->GetTransform()->GetPos() = _quad->GetTransform()->GetWorldPos();

	if (_quad->GetTransform()->GetScale().y < 0.3f)
	{
		_quad->GetTransform()->GetScale().y = 0.1f;
	}
}

void Bro_Player::Attack(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (auto bullet : _bullet)
	{	
		if (bullet->IsActive()== false) 
			return;

		for (const auto& monster : monsters)
		{
			if (bullet->GetCollider()->IsCollision(monster->GetCollider()))
			{
			SOUND->Play("Hit_Sound", 0.5f);
			monster->GetHp() -= _gun->DMG;

			if (monster->GetHp() < 0)
			{
				monster->GetHp() = 0;
				monster->Die();
				SceneManager::GetInstance()->AddPoints(100);
			}
			monster->Update();
			bullet->SetActive(false);
			return;
			}
		}
		if (!bullet->GetCollider()->IsCollision(_radious))
		{
			bullet->SetActive(false);
		}
	}
}

void Bro_Player::Attack_R(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (auto railbullet : _railbullet)
	{
		if (!railbullet->IsActive()) return;

		for (const auto& monster : monsters)
		{
			if (railbullet->GetCollider()->IsCollision(monster->GetCollider()))
			{
				SOUND->Play("Hit_Sound", 0.5f);
				monster->GetHp() -= _railgun->DMG;

				if (monster->GetHp() < 0)
				{
					monster->GetHp() = 0;
					monster->Die();
					SceneManager::GetInstance()->AddPoints(100);
				}
				monster->Update();
			}
		}
		if (!railbullet->GetCollider()->IsCollision(_radious_R))
		{
			railbullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
			railbullet->GetTransform()->Update();
			railbullet->SetActive(false);
			return;
		}
	}
}

void Bro_Player::Attack_SMG(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (auto smgbullet : _smgbullet)
	{
		if (smgbullet->IsActive() == false)
			return;
		for (const auto& monster : monsters)
		{
			if (smgbullet->GetCollider()->IsCollision(monster->GetCollider()))
			{
				SOUND->Play("Hit_Sound", 0.5f);
				monster->GetHp() -= _smg->DMG;

				if (monster->GetHp() < 0)
				{
					monster->GetHp() = 0;
					monster->Die();
					SceneManager::GetInstance()->AddPoints(100);
				}

			//	monster->Update();
				smgbullet->SetActive(false);
				return;
			}
		}
		if (!smgbullet->GetCollider()->IsCollision(_radious_SMG))
		{
			smgbullet->SetActive(false);
		}
	}
}

void Bro_Player::Target(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (auto& monster : monsters)
	{
		if (_radious->IsCollision(monster->GetCollider()))
		{
			_target = monster;
			break;
		}
		else
		{
			_target = nullptr;
		}
	}
	if (_target == nullptr)
	{
		for (auto bullet : _bullet)
		{
			if (!bullet->GetCollider()->IsCollision(_radious))
			{
				bullet->SetActive(false);
				return;
			}
		}
	}	
}

void Bro_Player::Target_R(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (auto& monster : monsters)
	{
		if (_radious_R->IsCollision(monster->GetCollider()))
		{
			_target_R = monster;
			break;
		}
		else
		{
			_target_R = nullptr;
		}
	}
	if (_target_R == nullptr)
	{
		for (auto railbullet : _railbullet)
		{
			if (!railbullet->GetCollider()->IsCollision(_radious_R))
			{
				railbullet->SetActive(false);
				return;
			}
		}
	}
}

void Bro_Player::Target_SMG(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (auto& monster : monsters)
	{
		if (_radious_SMG->IsCollision(monster->GetCollider()))
		{
			_target_SMG = monster;
			break;
		}
		else
		{
			_target_SMG = nullptr;
		}
	}
	if (_target_SMG == nullptr)
	{
		for (auto smgbullet : _smgbullet)
		{
			if (!smgbullet->GetCollider()->IsCollision(_radious_SMG))
			{
				smgbullet->SetActive(false);
				return;
			}
		}
	}
}

void Bro_Player::Shot()
{	
	if (_target == nullptr) 
		return;

	Vector2 direction = _target->GetCollider()->GetTransform()->GetWorldPos() - _firePos->GetWorldPos();
	float angle = direction.Angle();

	if (_fireCheck > _fireDelay)
	{
		_fireCheck = 0.0f;
	}
	else
		return;

	auto iter = std::find_if(_bullet.begin(), _bullet.end(), [](const shared_ptr<Bro_Player_Bullet>& bullet)
		{
			if (bullet->IsActive() == false)
				return true;
			return false;
		});

	if (iter != _bullet.end())
	{
		(*iter)->SetActive(true);
		(*iter)->GetTransform()->SetPos(_firePos->GetWorldPos());
		GetGun()->GetQuad()->GetTransform()->SetAngle(angle);
		GetGun()->GetCollider()->GetTransform()->SetAngle(angle);

		(*iter)->SetDirection(direction.Normal());
		(*iter)->GetQuad()->GetTransform()->SetAngle(angle);
		return;
	}	
}

void Bro_Player::Shot_R()
{
	if (_target_R == nullptr) return;
	Vector2 direction = _target_R->GetCollider()->GetTransform()->GetWorldPos() - _firePos_R->GetWorldPos();
	float angle = direction.Angle();

	if (_fireCheck_R > _fireDelay_R)
	{
		_fireCheck_R = 0.0f;
	}
	else
		return;

	auto iter = std::find_if(_railbullet.begin(), _railbullet.end(), [](const shared_ptr<Bro_player_Bullet_Rail>& bullet)
		{
			if (bullet->IsActive() == false)
				return true;
			return false;
		});

	if (iter != _railbullet.end())
	{
		(*iter)->GetTransform()->SetPos(_firePos_R->GetWorldPos());
		(*iter)->GetTransform()->Update();
		(*iter)->SetActive(true);
		GetRailGun()->GetQuad()->GetTransform()->SetAngle(angle);
	//	GetRailGun()->GetCollider()->GetTransform()->SetAngle(angle);

		(*iter)->SetDirection(direction.Normal());
		(*iter)->GetQuad()->GetTransform()->SetAngle(angle);
		return;
	}
}

void Bro_Player::Shot_SMG()
{	
	if (_target_SMG == nullptr) return;
	Vector2 direction = _target_SMG->GetCollider()->GetTransform()->GetWorldPos() - _firePos_SMG->GetWorldPos();
	float angle = direction.Angle();

	if (_fireCheck_S > _fireDelay_S)
	{
		_fireCheck_S = 0.0f;
	}
	else
		return;

	auto iter = std::find_if(_smgbullet.begin(), _smgbullet.end(), [](const shared_ptr<Bro_Player_Bullet_SMG>& bullet)
		{
			if (bullet->IsActive() == false)
				return true;
			return false;
		});

	if (iter != _smgbullet.end())
	{
		(*iter)->GetTransform()->SetPos(_firePos_SMG->GetWorldPos());
		(*iter)->GetTransform()->Update();
		(*iter)->SetActive(true);
		GetSMG()->GetQuad()->GetTransform()->SetAngle(angle);
	//	GetSMG()->GetCollider()->GetTransform()->SetAngle(angle);

		(*iter)->SetDirection(direction.Normal());
		(*iter)->GetQuad()->GetTransform()->SetAngle(angle);
		return;
	}
}

void Bro_Player::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;
}