#include "framework.h"
#include "Program.h"

Program::Program()
{
	Timer::GetInstance()->SetLockFPS(144);
}

Program::~Program()
{
}

void Program::Update()
{
	if (KEY_DOWN(VK_F1))
	{
		Collider::_isDebug = !Collider::_isDebug;
	}

	Keyboard::GetInstance()->Update();
	Timer::GetInstance()->Update();

	SCENE->Update();
	EFFECT->Update();

	Camera::GetInstance()->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	// imgui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Camera::GetInstance()->SetProjectionBuffer(WIN_WIDTH, WIN_HEIGHT);
	Camera::GetInstance()->SetCameraWorldBuffer();

	SCENE->PreRender();

	Camera::GetInstance()->SetViewPort();
	AlphaBlendState->SetState();

	// Scene Render
	SCENE->Render();
	EFFECT->Render();



	CAMERA->SetUICameraBuffer();
	Camera::GetInstance()->PostRender();
	SCENE->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
