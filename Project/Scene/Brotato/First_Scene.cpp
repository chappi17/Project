#include "framework.h"
#include "First_Scene.h"

First_Scene::First_Scene()
{
	wstring path(L"Effect/");
	_quad = make_shared<Quad>(path + L"First_Scene.jpg");
	_quad->GetTransform()->SetScale(Vector2{ 0.8f,0.7f });
	_quad->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
	_quad->Update();

	_button_Start = make_shared<Button>(L"Effect/Start.png");
	_button_Start->SetPostion(Vector2(CENTER_X-575, CENTER_Y-131));
	_button_Start->SetScale(Vector2(1.0f, 0.9f));

	_button_Exit = make_shared<Button>(L"Effect/Exit.png");
	_button_Exit->SetPostion(Vector2(CENTER_X - 575, CENTER_Y - 325));
	_button_Exit->SetScale(Vector2(0.9f, 0.9f));

	SOUND->Add("Click", "Resource/Brotato/Sound/Click.wav");

	_button_Start->SetEvent(std::bind(&First_Scene::ChangeScene_Stage0, this));
}

First_Scene::~First_Scene()
{
}

void First_Scene::ChangeScene_Stage0()
{
	SCENE->ChangeScene("Brotato_Store");
	SOUND->Play("Click");
}

void First_Scene::Update()
{
	_button_Start->Update();
	_button_Exit->Update();
}

void First_Scene::Render()
{
	_quad->Render();
	_button_Start->PostRender();
	_button_Exit->PostRender();
}
