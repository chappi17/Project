#include "framework.h"
#include "Store_menu.h"
#include "Scene/Brotato/BrotatoScene.h"

Store_menu::Store_menu()
{
	wstring path1 = (L"UI/");
	_quad_G = make_shared<Quad>(path1 + L"store_menu_G.png");
	_quad_G->GetTransform()->GetPos() = { CENTER_X - 480,CENTER_Y + 50 };
	_quad_G->GetTransform()->GetScale() * 0.5f;

	wstring path2 = (L"UI/");
	_quad_R = make_shared<Quad>(path2 + L"store_menu_R.png");
	_quad_R->GetTransform()->GetPos() = { CENTER_X - 155,CENTER_Y + 50 };

	wstring path3 = (L"UI/");
	_quad_SMG = make_shared<Quad>(path3 + L"store_menu_SMG.png");
	_quad_SMG->GetTransform()->GetPos() = { CENTER_X + 175,CENTER_Y + 50 };


	_button_G = make_shared<Button>(L"UI/button_hover.png");

	_button_G->SetPostion(Vector2(CENTER_X - 480, CENTER_Y - 100));
	_button_G->SetScale(Vector2(0.9f, 0.8f));

	_button_R = make_shared<Button>(L"UI/button_hover.png");
	_button_R->SetPostion(Vector2(CENTER_X - 150, CENTER_Y - 100));
	_button_R->SetScale(Vector2(0.9f, 0.8f));

	_button_SMG = make_shared<Button>(L"UI/button_hover.png");
	_button_SMG->SetPostion(Vector2(CENTER_X + 180, CENTER_Y -100));
	_button_SMG->SetScale(Vector2(0.9f, 0.8f));

	_icon = make_shared<Bro_icon>();

	SOUND->Add("Click", "Resource/Brotato/Sound/Click.wav");


	_button_G->SetEvent(std::bind(&Store_menu::Unlock_Gun, this));
	_button_R->SetEvent(std::bind(&Store_menu::Unlock_rail, this));
	_button_SMG->SetEvent(std::bind(&Store_menu::Unlock_smg, this));
}

Store_menu::~Store_menu()
{
}

void Store_menu::Update()
{
	_quad_G->Update();
	_quad_R->Update();
	_quad_SMG->Update();

	_button_G->Update();
	_button_R->Update();
	_button_SMG->Update();

	_icon->Update();
}

void Store_menu::Render()
{
	_quad_G->Render();
	_quad_R->Render();
	_quad_SMG->Render();

	_button_G->PostRender();
	_button_R->PostRender();
	_button_SMG->PostRender();

	_icon->Render();
}

void Store_menu::PostRender()
{

}

void Store_menu::Unlock_Gun()
{
	if (SCENE->GetPoints() == 0)
	{	
		_icon->GetGun()->GetTransform()->GetPos() = { CENTER_X - 480 ,CENTER_Y - 300 };
		SCENE->SetUnlock_G(true);
		SOUND->Play("Click");
		return;
	}
	if (SCENE->GetPoints() >= 500)
	{
	SCENE->AddPoints(-500);
	}
	else
	{
		return;
	}

	_icon->GetGun()->GetTransform()->GetPos() = { CENTER_X - 480 ,CENTER_Y - 300 };
	SCENE->SetUnlock_G(true);
	SOUND->Play("Click");
}

void Store_menu::Unlock_rail()
{
	if (SCENE->GetPoints() == 0)
	{
		_icon->Getrailgun()->GetTransform()->GetPos() = { CENTER_X - 340 ,CENTER_Y - 300 };
		SCENE->SetUnlock_R(true);
		SOUND->Play("Click");
		return;
	}
	if (SCENE->GetPoints() >= 1000)
	{
		SCENE->AddPoints(-1000);
	}
	else
	{
		return;
	}
	_icon->Getrailgun()->GetTransform()->GetPos() = { CENTER_X - 340 ,CENTER_Y - 300 };
	SCENE->SetUnlock_R(true);
	SOUND->Play("Click");
}

void Store_menu::Unlock_smg()
{
	if (SCENE->GetPoints() == 0)
	{

		_icon->Getsmg()->GetTransform()->GetPos() = { CENTER_X - 410 ,CENTER_Y - 300 };
		SCENE->SetUnlock_S(true);
		SOUND->Play("Click");
		return;
	}

	if (SCENE->GetPoints() >= 800)
	{
	SCENE->AddPoints(-800);
	}
	else
	{
		return;
	}

	_icon->Getsmg()->GetTransform()->GetPos() = { CENTER_X - 410 ,CENTER_Y - 300 };
	SCENE->SetUnlock_S(true);
	SOUND->Play("Click");
}
