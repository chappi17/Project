#include "framework.h"
#include "Brotato_Store.h"

Brotato_Store::Brotato_Store()
{

	_button = make_shared<Button>(L"UI/button.png");
	_button->SetPostion(Vector2(CENTER_X, CENTER_Y));
	_button->SetScale(Vector2(0.7f,0.6f));
}

Brotato_Store::~Brotato_Store()
{
}

void Brotato_Store::Update()
{
	_button->Update();
}

void Brotato_Store::Render()
{
}

void Brotato_Store::PostRender()
{
	ImGui::Button("Save", ImVec2(50, 50));
	ImGui::Button("Load", ImVec2(50, 50));

	_button->PostRender();
}

void Brotato_Store::Save()
{
	BinaryWriter writer = BinaryWriter(L"Resource/Brotato/Save/text.txt");

}

void Brotato_Store::Load()
{
	BinaryReader reader = BinaryReader(L"Resource/Brotato/Save/text.txt");
}
