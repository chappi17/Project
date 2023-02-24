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

	_player->GetGun()->SetActive(false);
	_player->GetRailGun()->SetActive(false);
	_player->GetSMG()->SetActive(false);
	_bg->Update();

}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{

	if (SCENE->Unlock_Gun() == true)
	{
		_player->GetGun()->SetActive(true);
	}

	if (SCENE->Unlock_Rail() == true)
	{
		_player->GetRailGun()->SetActive(true);
	}

	if (SCENE->Unlock_SMG() == true)
	{
		_player->GetSMG()->SetActive(true);
	}
	_player->Update();

	if (TimeSet_res >= 5)
	{
		CreateMonsters();
		TimeSet_res = 0;
	}

	for (auto monster : _monsters)
	{
		monster->Update();
		monster->Attack(_player);
		

		if (_player->GetHp() <= 0)
		{
			_player->Attack(_monsters);
			_player->Dead();
			_player->SetActive(false);
		}

		if (_player->GetGun()->IsActive() == true)
		{
			_player->Attack(_monsters);
			_player->Target(_monsters);
			_player->Shot();
		}

		if (_player->GetRailGun()->IsActive() == true)
		{
			_player->Attack_R(_monsters);
			_player->Target_R(_monsters);
			_player->Shot_R();
		}

		if (_player->GetSMG()->IsActive() == true)
		{
			_player->Attack_SMG(_monsters);
			_player->Target_SMG(_monsters);
			_player->Shot_SMG();
		}

		for (auto monster2 : _monsters)
		{
			if (monster->GetCollider() != monster2->GetCollider() && monster->GetCollider()->IsCollision(monster2->GetCollider()))
			{
				auto collider1 = dynamic_pointer_cast<CircleCollider>(monster->GetCollider());
				auto collider2 = dynamic_pointer_cast<CircleCollider>(monster2->GetCollider());

			if (collider1 && collider2)
				{
					collider1->Block(collider2);
				if (_player->GetHp() <= 0)
					{
						_player->SetActive(false);
					}
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

	if (stage0 == false)
	{
		ChangeScene();
		stage0 = true;
	}

	// 20 초 지나면 상점전환
	TimeSet += DELTA_TIME;
	TimeSet_res += DELTA_TIME;


	if (TimeSet >= 20)
	{
		_player->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
		ChangeScene();
		TimeSet = 0;
	}
}

void BrotatoScene::Render()
{
	_bg->Render();
	for (auto monster : _monsters)
	{
		monster->Render();
	}
	_player->Render();

}

void BrotatoScene::PostRender()
{
	int playerHP = _player->GetHp();
	int Score = SceneManager::GetInstance()->GetPoints();
	
	wstring time = L"TIME : " + to_wstring((int)TimeSet);
	RECT rect2 = { 100,100,100,100 };
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(time,rect);

	ImGui::SliderInt("playerHp", &playerHP, 0, 10);
	ImGui::SliderInt("Points: ", &Score, 0, 50000);
}

void BrotatoScene::CreateMonsters()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 5; i++)
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
	TimeSet = 0;
	_player->GetTransform()->SetPos(Vector2{ CENTER_X,CENTER_Y });
	_player->SetActive(true);

	_monsters.clear();
	CreateMonsters();
}

void BrotatoScene::ChangeScene()
{
	SCENE->ChangeScene("Brotato_Store");
	Reset();
}

void BrotatoScene::End_Stage()
{
	_player->Dead();
	for (auto monster : _monsters)
	{
		monster->Dead();
	}
}

void BrotatoScene::Init()
{
}


