#include "framework.h"
#include "BrotatoScene.h"


BrotatoScene::BrotatoScene()
{
	_camera = make_shared<Transform>();
	_camera->GetPos() = { CENTER_X,CENTER_Y };
	_monster_manager = make_shared<Monster_manager>();
	_monster_manager->CreateMonsters();

	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });	
	
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

	_monster_manager->Update();


	
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

	if (TimeSet_res > 10)
	{
		_monster_manager->CreateMonsters();
		TimeSet_res = 0;
	}


	if (_player->GetHp() <= 0)
	{
		_player->Attack(_monster_manager->_monsters);
		_player->Dead();
		_player->SetActive(false);
	}

	if (_player->GetGun()->IsActive() == true)
	{
		_player->Attack(_monster_manager->_monsters);
		_player->Target(_monster_manager->_monsters);
		_player->Shot();
	}

	if (_player->GetRailGun()->IsActive() == true)
	{
		_player->Attack_R(_monster_manager->_monsters);
		_player->Target_R(_monster_manager->_monsters);
		_player->Shot_R();
	}

	if (_player->GetSMG()->IsActive() == true)
	{
		_player->Attack_SMG(_monster_manager->_monsters);
		_player->Target_SMG(_monster_manager->_monsters);
		_player->Shot_SMG();
	}

	for (auto monster : _monster_manager->_monsters)
	{
		monster->Update();
		monster->Attack(_player);

		for (auto monster2 : _monster_manager->_monsters)
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
		_monster_manager->LeftRight(_player);
	}


	/*	if (KEY_DOWN(VK_F3))
	{
		_player->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
		ChangeScene();
	}*/	

	// 20 초 지나면 상점전환
	TimeSet += DELTA_TIME;
	TimeSet_res += DELTA_TIME;
	SCENE->SetStage(true);

	if (TimeSet >= 20)
	{
		_player->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
		ChangeScene();
		TimeSet = 0;
		++_countStage;
	}
}

void BrotatoScene::Render()
{

	_bg->Render();

	_player->Render();

	wstring time = L"시간  " + to_wstring((int)TimeSet);
	RECT rect2 = { 600,0,660,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(time, rect2, 30.0f);

	DirectWrite::GetInstance()->GetDC()->EndDraw();
//	Device::GetInstance()->Present();

	_monster_manager->Render();

}

void BrotatoScene::PostRender()
{
	int playerHP = _player->GetHp();
	int Score = SceneManager::GetInstance()->GetPoints();
	int Stage = _countStage;

	ImGui::SliderInt("playerHp", &playerHP, 0, 10);
	ImGui::SliderInt("Points: ", &Score, 0, 50000);
	ImGui::SliderInt("Stage", &Stage, 0, 10);
}

void BrotatoScene::Reset()
{
	_monster_manager->_monsters.clear();
	_player->GetHp() = 12;
	TimeSet = 0;
	_player->GetTransform()->SetPos(Vector2{ CENTER_X,CENTER_Y });
	_player->SetActive(true);	
}

void BrotatoScene::ChangeScene()
{
	SCENE->ChangeScene("Brotato_Store");
	Reset();
}

void BrotatoScene::FirstScene()
{
	SCENE->ChangeScene("First_Scene");
}

void BrotatoScene::End_Stage()
{
	_player->Dead();
}

void BrotatoScene::Init()
{
}


