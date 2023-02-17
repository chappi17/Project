#include "framework.h"
#include "Bro_icon.h"

Bro_icon::Bro_icon()
{
	wstring path = (L"Player/");
	_player_icon = make_shared<Quad>(path + L"Player_1.png");
	_player_icon->GetTransform()->GetPos() = { CENTER_X - 550 ,CENTER_Y - 300 };

	wstring path2 = (L"Item_gun/");
	_gun_icon = make_shared<Quad>(path2 + L"item_gun.png");
	_gun_icon->GetTransform()->GetPos() = { CENTER_X - 480 ,CENTER_Y - 300 }; 
	_gun_icon->GetTransform()->GetScale().x *= 0.07f;
	_gun_icon->GetTransform()->GetScale().y *= 0.07f;

	wstring path3 = (L"Item_gun/");
	_railgun_icon = make_shared<Quad>(path3 + L"item_railgun.png");
	_railgun_icon->GetTransform()->GetPos().x = -3000;
	
	_railgun_icon->GetTransform()->GetScale().x *= 0.07f;
	_railgun_icon->GetTransform()->GetScale().y *= 0.07f;

	wstring path4 = (L"Item_gun/");
	_smg_icon = make_shared<Quad>(path4 + L"item_smg.png");
	_smg_icon->GetTransform()->GetPos().x = -3000;
	
	_smg_icon->GetTransform()->GetScale().x *= 0.07f;
	_smg_icon->GetTransform()->GetScale().y *= 0.07f;
}

Bro_icon::~Bro_icon()
{
}

void Bro_icon::Update()
{
	_player_icon->Update();
	_gun_icon->Update();
	_railgun_icon->Update();
	_smg_icon->Update();
}

void Bro_icon::Render()
{
	_player_icon->Render();
	_gun_icon->Render();
	_railgun_icon->Render();
	_smg_icon->Render();
}

void Bro_icon::PostRender()
{
}

void Bro_icon::SetActive(bool isActive)
{
	_isActive = isActive;
}

