#include "framework.h"
#include "BrotatoScene.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	_bg->Update();
}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
	_player->Update();
}

void BrotatoScene::Render()
{
	_bg->Render();
	_player->Render();
}
