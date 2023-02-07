#include "framework.h"
#include "BrotatoScene.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });

	for (int i = 0; i < 100; i++)
	{
		auto monster = make_shared<Bro_Monster>();
		if (i < 30)
		
			monster->isActive = true;
			_monsters.push_back(monster);		
	}
	_bg->Update();
}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
	_player->Update();
	_player->GetGun()->Target(_monsters);

	for (auto monster : _monsters)
	{		
		monster->Update();
		monster->Attack(_player);

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
