#include "framework.h"
#include "BrotatoScene.h"

BrotatoScene::BrotatoScene()
{
	_bg = make_shared<Bro_BackGround>();
	_bg->Update();
}

BrotatoScene::~BrotatoScene()
{
}

void BrotatoScene::Update()
{
}

void BrotatoScene::Render()
{
	_bg->Render();
}
