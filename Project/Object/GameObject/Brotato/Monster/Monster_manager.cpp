#include "framework.h"
#include "Monster_manager.h"
#include "time.h"
class Bro_Player;

Monster_manager::Monster_manager()
{
	CreateMonsters();

	wstring path = (L"Monster/");
	_quad = make_shared<Quad>(path + L"Monster1.png");
	_quad->SetVertexShader(ADD_VS(L"InstanceVertexShader"));
	_quad->SetPixelShader(ADD_PS(L"InstancePixelShader"));
}

Monster_manager::~Monster_manager()
{
}

void Monster_manager::CreateMonsters()
{
	srand((unsigned int)time(NULL));

	vector<float> respawnXPos(30);
	vector<float> respawnYPos(30);

	_instanceDataes.resize(15);

	for (int i = 0; i < 15; i++)
	{
		respawnXPos[i] = rand() % ((WIN_WIDTH + 100) - (-100) + 1) + (-100);
		respawnYPos[i] = rand() % ((WIN_HEIGHT + 260) - (-260) + 1) + (-260);
	}

	for (int i = 0; i < 15; i++)
	{
		auto monster = make_shared<Bro_Monster>();
		monster->GetTransform()->GetPos() = Vector2{ respawnXPos[i], respawnYPos[i] };
		monster->Update();
		monster->SetActive(true);
		_monsters.push_back(monster);
	}
		_instanceBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(InstanceData), 15, 0, true);
}

void Monster_manager::LeftRight(shared_ptr<Bro_Player> player)
{
	if (player->GetTransform()->GetWorldPos().x > _quad->GetTransform()->GetWorldPos().x)
	{
		_quad->SetLeftRight_leftRightBuffer(0);
	}

	if (player->GetTransform()->GetWorldPos().x < _quad->GetTransform()->GetWorldPos().x)
	{
		_quad->SetLeftRight_leftRightBuffer(1);
	}
}

void Monster_manager::Update()
{	
	for (int i = 0; i < 15; i++)
	{	
		_monsters[i]->GetTransform()->GetScale().x = 0.1f;
		_monsters[i]->GetTransform()->GetScale().y = 0.1f;
		_instanceDataes[i].matrix = XMMatrixTranspose(*_monsters[i]->GetTransform()->GetMatrix());
		_instanceBuffer->Update();
	}
}

void Monster_manager::Render()
{
	_instanceBuffer->IASet(1);
	_quad->SetRender();

	DC->DrawIndexedInstanced(6, 100, 0, 0, 0);
	for (auto monster : _monsters)
	{
		monster->Render();
	}
}
