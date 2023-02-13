#include "framework.h"
#include "BrotatoScene.h"
#include "time.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });

	for (int i = 0; i < 5; i++)
	{
		auto monster = make_shared<Bro_Monster>();
		{
		//	srand((unsigned int)time(NULL));
			float RespawnX = monster->GetTransform()->GetPos().x = rand() % ((WIN_WIDTH + 100) - (-100) + 1) + (-100);
			float RespawnY = monster->GetTransform()->GetPos().y = rand() % ((WIN_HEIGHT + 260) - (-260) + 1) + (-260);

			monster->GetTransform()->GetPos() = Vector2{ RespawnX,RespawnY };
			monster->Update();
			monster->isActive = true;
			_monsters.push_back(monster);
		}
	}
	_bg->Update();
}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
	_player->Update();

	for (auto monster : _monsters)
	{			
		monster->Attack(_player);

		_player->Target(_monsters);
		_player->Attack(_monsters);
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
