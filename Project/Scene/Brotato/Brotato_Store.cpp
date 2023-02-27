#include "framework.h"
#include "Brotato_Store.h"
#include "Scene/Brotato/BrotatoScene.h"
#include "Object/GameObject/Brotato/Player/Bro_Player.h"

Brotato_Store::Brotato_Store()
{
	_menu = make_shared<Store_menu>();

	_button_Next_Wave = make_shared<Button>(L"UI/Next_Stage.png");
	_button_Next_Wave->SetPostion(Vector2(CENTER_X + 470, CENTER_Y - 300));
	_button_Next_Wave->SetScale(Vector2(1.7f, 1.0f));

	_button_Next_Wave->SetEvent(std::bind(&Brotato_Store::ChangeScene_Game, this));

	SOUND->Add("Click", "Resource/Brotato/Sound/Click.wav");
}

Brotato_Store::~Brotato_Store()
{
}

void Brotato_Store::Update()
{
	_menu->Update();
	_button_Next_Wave->Update();
}

void Brotato_Store::Render()
{
	_menu->Render();
	_button_Next_Wave->PostRender();

	wstring price = L"500 ";
	RECT rect1 = { 135,440,660,600 };

	wstring price2 = L"1000 ";
	RECT rect2 = { 455,440,660,600 };

	wstring price3 = L"800 ";
	RECT rect3 = { 1195,440,800,1600 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(price, rect1,30.0f);
	DirectWrite::GetInstance()->RenderText(price2, rect2, 30.0f);
	DirectWrite::GetInstance()->RenderText(price3, rect3, 30.0f);

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}

void Brotato_Store::PostRender()
{
	int score = SceneManager::GetInstance()->GetPoints();
	ImGui::SliderInt("Points:", &score, 0, 50000);
}

void Brotato_Store::Save_Slot()
{


}

void Brotato_Store::Load_Slot()
{

}

void Brotato_Store::ChangeScene_Game()
{
	SCENE->ChangeScene("BroScene");
	SOUND->Play("Click");
}
