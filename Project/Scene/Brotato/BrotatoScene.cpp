#include "framework.h"
#include "BrotatoScene.h"
#include "time.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });

	CreateMonsters();
	_bg->Update();
}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
	_player->Update();

	if (_player->GetHp() <= 0)
	{
		_player->SetActive(false);
		Reset();
	}


	for (auto monster : _monsters)
	{
		monster->Attack(_player);

		_player->Target(_monsters);
		_player->Shot();
		_player->Attack(_monsters);

		_player->Target_R(_monsters);
		_player->Shot_R();
		_player->Attack_R(_monsters);

		_player->Target_SMG(_monsters);
		_player->Shot_SMG();
		_player->Attack_SMG(_monsters);

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

	// 20 초 지나면 상점전환
	if (Timer::GetInstance()->GetRunTime() >= 20)
	{
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
	for (int i = 0; i < 10; i++)
	{
		auto monster = make_shared<Bro_Monster>();
		{
			//	srand((unsigned int)time(NULL));
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
	CreateMonsters();
}

void BrotatoScene::ChangeScene()
{
	SCENE->ChangeScene("Brotato_Store");
}
