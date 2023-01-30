#include "framework.h"
#include "BrotatoScene.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_player = make_shared<Bro_Player>();
	_bg->Update();


	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetOffSet({ CENTER_X,CENTER_Y });
	CAMERA->SetLeftBottom(_bg->GetSize() * 0.5f + _bg->GetMainPos());
	CAMERA->SetRightTop(_bg->GetSize() * 0.5f + _bg->GetMainPos());
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
