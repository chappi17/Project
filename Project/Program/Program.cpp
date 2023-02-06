#include "framework.h"
#include "Program.h"

Program::Program()
{
	
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

	Camera::GetInstance()->SetProjectionBuffer(WIN_WIDTH, WIN_HEIGHT);
	Camera::GetInstance()->SetCameraWorldBuffer();

	SCENE->PreRender();

	Camera::GetInstance()->SetViewPort();
	AlphaBlendState->SetState();

	// Scene Render
	SCENE->Render();
	EFFECT->Render();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);

	CAMERA->SetUICameraBuffer();
	Camera::GetInstance()->PostRender();
	SCENE->PostRender();

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
