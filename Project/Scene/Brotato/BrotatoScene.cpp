#include "framework.h"
#include "BrotatoScene.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	_monster = make_shared<Bro_Monster>();
	_bg->Update();

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });

}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
	_monster->Attack(_player);
	_player->Update();
	_monster->Update();
}

void BrotatoScene::Render()
{
	_bg->Render();
	_player->Render();
	_monster->Render();
}
