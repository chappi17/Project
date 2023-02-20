#include "framework.h"
#include "BrotatoScene.h"
#include "time.h"

BrotatoScene::BrotatoScene()
{
	_camera = make_shared<Transform>();
	_camera->GetPos() = { CENTER_X,CENTER_Y };

	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });

	CreateMonsters();

	_player->GetRailGun()->SetActive(false);
	_player->GetSMG()->SetActive(false);
	_bg->Update();
}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
	if (SCENE->Unlock_Rail() == true)
	{
		_player->GetRailGun()->SetActive(true);
	}

	if (SCENE->Unlock_SMG() == true)
	{
		_player->GetSMG()->SetActive(true);
	}

	_player->Update();


	for (auto monster : _monsters)
	{
		monster->Attack(_player);

		_player->Attack(_monsters);
		_player->Target(_monsters);
		_player->Shot();


		if (_player->GetRailGun()->IsActive() == true)
		{
			_player->Target_R(_monsters);
			_player->Shot_R();
			_player->Attack_R(_monsters);
		}

		if (_player->GetSMG()->IsActive() == true)
		{
			_player->Target_SMG(_monsters);
			_player->Shot_SMG();
			_player->Attack_SMG(_monsters);
		}

		monster->Update();

		for (auto monster2 : _monsters)
		{
			if (monster->GetCollider() != monster2->GetCollider() && monster->GetCollider()->IsCollision(monster2->GetCollider()))
			{
				auto collider1 = dynamic_pointer_cast<CircleCollider>(monster->GetCollider());
				auto collider2 = dynamic_pointer_cast<CircleCollider>(monster2->GetCollider());

				if (collider1 && collider2)
				{
					collider1->Block(collider2);
				}
			}
		}
		monster->LeftRight(_player);
	}

	if (KEY_DOWN(VK_F3))
	{
		_player->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
		ChangeScene();
	}

	// 20 초 지나면 상점전환
	if (Timer::GetInstance()->GetElasedTime() >= 20)
	{
		_player->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
		ChangeScene();
	}
}

void BrotatoScene::Render()
{
	_bg->Render();
	_player->Render();
	for (auto monster : _monsters)
	{
		monster->Render();
	}
}

void BrotatoScene::PostRender()
{
	int playerHP = _player->GetHp();

	ImGui::SliderInt("playerHp", &playerHP, 0, 10);
	
}

void BrotatoScene::CreateMonsters()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10; i++)
	{
		auto monster = make_shared<Bro_Monster>();
		{
			float RespawnX = monster->GetTransform()->GetPos().x = rand() % ((WIN_WIDTH + 100) - (-100) + 1) + (-100);
			float RespawnY = monster->GetTransform()->GetPos().y = rand() % ((WIN_HEIGHT + 260) - (-260) + 1) + (-260);

			monster->GetTransform()->GetPos() = Vector2{ RespawnX,RespawnY };
			monster->Update();
			monster->SetActive(true);
			_monsters.push_back(monster);
		}
	}
	
}

void BrotatoScene::Reset()
{
	_player->GetHp() = 12;
	_player->GetTransform()->SetPos(Vector2{ CENTER_X,CENTER_Y });
	_player->SetActive(true);

	//for (auto monster : _monsters)
	//{
	//	monster->SetActive(false);
	//}
	CreateMonsters();
}

void BrotatoScene::ChangeScene()
{
	SCENE->ChangeScene("Brotato_Store");
	Reset();
}

void BrotatoScene::Init()
{
}


