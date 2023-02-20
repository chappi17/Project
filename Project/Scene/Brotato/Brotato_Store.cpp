#include "framework.h"
#include "Brotato_Store.h"

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

	wstring Next_Round = L"다음 게임 : ";
	RECT rect = { -100,0,100,100 };
	RECT rect2 = { 100,0,200,200 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(Next_Round, rect);

}

void Brotato_Store::Render()
{
	_menu->Render();
	_button_Next_Wave->PostRender();
}

void Brotato_Store::PostRender()
{
	//ImGui::Button("Save", ImVec2(50, 50));
	//ImGui::Button("Load", ImVec2(50, 50));

	//ImGui::SliderFloat2("ItemX", &_quad->GetTransform()->GetPos().x, 0.0f, WIN_WIDTH);
	//ImGui::SliderFloat2("ItemY", &_quad->GetTransform()->GetPos().y, 0.0f, WIN_HEIGHT);


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
