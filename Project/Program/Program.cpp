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

	// 20 초 지나면 상점전환
	if (Timer::GetInstance()->GetRunTime() >= 20)
	{

	}
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
	RECT rect2 = { 100,0,200,200 };

	wstring time = L"TIME : " + to_wstring((int)Timer::GetInstance()->GetRunTime());

	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);
	DirectWrite::GetInstance()->RenderText(time, rect2);



	CAMERA->SetUICameraBuffer();
	Camera::GetInstance()->PostRender();
	SCENE->PostRender();

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
