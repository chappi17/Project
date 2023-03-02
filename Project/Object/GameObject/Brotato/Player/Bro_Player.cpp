#include "framework.h"
#include "Bro_Player.h"

Bro_Player::Bro_Player()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<CircleCollider>(25);

	_radious = make_shared<CircleCollider>(300);
	_radious_R = make_shared<CircleCollider>(380);
	_radious_SMG = make_shared<CircleCollider>(290);

	_bullet = make_shared<Bro_Player_Bullet>();
	_railbullet = make_shared<Bro_player_Bullet_Rail>();
	_smgbullet = make_shared<Bro_Player_Bullet_SMG>();
	
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

	_bullet->Update();

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

	_bullet->Update();
	_railbullet->Update();
	_smgbullet->Update();

	EFFECT->Update();

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

	_bullet->Render();
	_railbullet->Render();
	_smgbullet->Render();

	EFFECT->Render();
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
	if (!_bullet->IsActive()) return;
	for (const auto& monster : monsters)
	{
		if (_bullet->GetCollider()->IsCollision(monster->GetCollider()))
		{
			SOUND->Play("Hit_Sound",0.1f);
			monster->GetHp() -= _gun->DMG;

			if (monster->GetHp() < 0)
			{
				monster->GetHp() = 0;
				monster->Die();
				SceneManager::GetInstance()->AddPoints(100);
			}

			monster->Update();
			_bullet->SetActive(false);
			_bullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
			_bullet->GetTransform()->Update();
			return;
		}
	}
	if (!_bullet->GetCollider()->IsCollision(_radious))
	{
		_bullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
		_bullet->GetTransform()->Update();
		_bullet->SetActive(false);
		return;
	}

}

void Bro_Player::Attack_R(vector<shared_ptr<Bro_Monster>>& monsters)
{
	if (!_railbullet->IsActive()) return;

	for (const auto& monster : monsters)
	{
		if (_railbullet->GetCollider()->IsCollision(monster->GetCollider()))
		{
			SOUND->Play("Hit_Sound",0.1f);
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
	if (!_railbullet->GetCollider()->IsCollision(_radious_R))
	{
		_railbullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
		_railbullet->GetTransform()->Update();
		_railbullet->SetActive(false);
		return;
	}
}

void Bro_Player::Attack_SMG(vector<shared_ptr<Bro_Monster>>& monsters)
{
	if (!_smgbullet->IsActive()) return;

	for (const auto& monster : monsters)
	{
		if (_smgbullet->GetCollider()->IsCollision(monster->GetCollider()))
		{
			SOUND->Play("Hit_Sound",0.1f);
			monster->GetHp() -= _smg->DMG;

			if (monster->GetHp() < 0)
			{
				monster->GetHp() = 0;
				monster->Die();
				SceneManager::GetInstance()->AddPoints(100);
			}

			monster->Update();
			_smgbullet->SetActive(false);
			_smgbullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
			_smgbullet->GetTransform()->Update();
			return;
		}
	}
	if (!_smgbullet->GetCollider()->IsCollision(_radious_SMG))
	{
		_smgbullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
		_smgbullet->GetTransform()->Update();
		_smgbullet->SetActive(false);
		return;
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
		if (!_bullet->GetCollider()->IsCollision(_radious))
		{
			_bullet->SetActive(false);
			return;
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
		if (!_railbullet->GetCollider()->IsCollision(_radious_R))
		{
			_railbullet->SetActive(false);
			return;
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
		if (!_smgbullet->GetCollider()->IsCollision(_radious_SMG))
		{
			_smgbullet->SetActive(false);
			return;
		}
	}
}

void Bro_Player::Shot()
{
	
	if (_fireCheck > _fireDelay)
	{
		_fireCheck = 0.0f;
	}
	else
		return;

	if (_target == nullptr) return;

	if (_bullet->IsActive() == false)
	{
		Vector2 direction = _target->GetCollider()->GetTransform()->GetWorldPos() - _firePos->GetWorldPos();
		float angle = direction.Angle();

		SOUND->Play("Shot", 0.05f);
		_bullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
		_bullet->GetTransform()->Update();
		_bullet->SetActive(true);
		GetGun()->GetQuad()->GetTransform()->SetAngle(angle);
		GetGun()->GetCollider()->GetTransform()->SetAngle(angle);

		_bullet->SetDirection(direction.Normal());
		_bullet->GetTransform()->SetPos((_firePos->GetWorldPos()));
		_bullet->GetQuad()->GetTransform()->SetAngle(angle);
		return;
	}


}

void Bro_Player::Shot_R()
{
	if (_fireCheck_R > _fireDelay_R)
	{
		_fireCheck_R = 0.0f;
	}
	else
		return;

	if (_target_R == nullptr) return;

	if (_railbullet->IsActive() == false)
	{
		Vector2 direction = _target_R->GetCollider()->GetTransform()->GetWorldPos() - _firePos_R->GetWorldPos();
		float angle = direction.Angle();

		SOUND->Play("Shot_R", 0.05f);

		_railbullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
		_railbullet->GetTransform()->Update();
		_railbullet->SetActive(true);
		GetRailGun()->GetQuad()->GetTransform()->SetAngle(angle);
		GetRailGun()->GetCollider()->GetTransform()->SetAngle(angle);

		_railbullet->SetDirection(direction.Normal());
		_railbullet->GetTransform()->SetPos((_firePos_R->GetWorldPos()));
		_railbullet->GetQuad()->GetTransform()->SetAngle(angle);
		return;
	}


}

void Bro_Player::Shot_SMG()
{	
	if (_fireCheck_S > _fireDelay_S)
	{
		_fireCheck_S = 0.0f;
	}
	else
		return;

	if (_target_SMG == nullptr) return;


	if (_smgbullet->IsActive() == false)
	{
		Vector2 direction = _target_SMG->GetCollider()->GetTransform()->GetWorldPos() - _firePos_SMG->GetWorldPos();
		float angle = direction.Angle();

		SOUND->Play("Shot_SMG", 0.1f);
		_smgbullet->GetTransform()->SetPos(_quad->GetTransform()->GetWorldPos());
		_smgbullet->GetTransform()->Update();
		_smgbullet->SetActive(true);

		GetSMG()->GetQuad()->GetTransform()->SetAngle(angle);
		GetSMG()->GetCollider()->GetTransform()->SetAngle(angle);

		_smgbullet->SetDirection(direction.Normal());
		_smgbullet->GetTransform()->SetPos((_firePos_SMG->GetWorldPos()));
		_smgbullet->GetQuad()->GetTransform()->SetAngle(angle);
		return;
	}
}

void Bro_Player::SetActive(bool isActive)
{
	_isActive = isActive;
	_collider->_isActive = isActive;
}