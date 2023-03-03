#include "framework.h"
#include "Monster_manager.h"
#include "time.h"
class Bro_Player;

Monster_manager::Monster_manager()
{
	CreateMonsters();
}

Monster_manager::~Monster_manager()
{
}

void Monster_manager::CreateMonsters()
{
	srand((unsigned int)time(NULL));

	vector<float> respawnXPos(30);
	vector<float> respawnYPos(30);

	

	for (int i = 0; i < respown; i++)
	{
		respawnXPos[i] = rand() % ((WIN_WIDTH + 100) - (-100) + 1) + (-100);
		respawnYPos[i] = rand() % ((WIN_HEIGHT + 260) - (-260) + 1) + (-260);
	}

	for (int i = 0; i < respown; i++)
	{
		auto monster = make_shared<Bro_Monster>();
		monster->GetTransform()->GetPos() = Vector2{ respawnXPos[i], respawnYPos[i] };
		monster->Update();
		monster->SetActive(true);
		_monsters.push_back(monster);
	}
}

void Monster_manager::CreateBoss()
{
	vector<float> respawnXPos(30);
	vector<float> respawnYPos(30);

	for (int i = 0; i < 2; i++)
	{
		respawnXPos[i] = rand() % ((WIN_WIDTH + 100) - (-100) + 1) + (-100);
		respawnYPos[i] = rand() % ((WIN_HEIGHT + 260) - (-260) + 1) + (-260);
	}

	for (int i = 0; i < 2; i++)
	{
		auto boss = make_shared<Bro_Boss>();
		boss->GetTransform()->GetPos() = Vector2{ respawnXPos[i], respawnYPos[i] };
		boss->Update();
		boss->SetActive(true);
		_boss.push_back(boss);
	}
}

void Monster_manager::LeftRight(shared_ptr<Bro_Player> player)
{
	for (auto monster : _monsters)
	{
		monster->LeftRight(player);
	}

	for (auto monster : _boss)
	{
		monster->LeftRight(player);
	}
}

void Monster_manager::Update()
{	
	//for (int i = 0; i < 15; i++)
	//{	
	//	_monsters[i]->GetTransform()->GetScale().x = 0.1f;
	//	_monsters[i]->GetTransform()->GetScale().y = 0.1f;
	//	_instanceDataes[i].matrix = XMMatrixTranspose(*_monsters[i]->GetTransform()->GetMatrix()); ***
	//	_instanceBuffer->Update(); ****
	//}

	for (auto monster : _monsters)
	{
		monster->Update();
	}

	for (auto boss : _boss)
	{
		boss->Update();
	}
}

void Monster_manager::Render()
{
	for (auto monster : _monsters)
	{
		monster->Render();
	}

	for (auto boss : _boss)
	{
		boss->Render();
	}
}
