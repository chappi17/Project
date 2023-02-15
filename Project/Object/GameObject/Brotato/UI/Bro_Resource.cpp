#include "framework.h"
#include "Bro_Resource.h"

Bro_Resource::Bro_Resource()
{
	wstring path = (L"Effect");
	_quad = make_shared<Quad>(path + L"resource.png");
}

Bro_Resource::~Bro_Resource()
{
}

void Bro_Resource::Update()
{
	_quad->Update();
}

void Bro_Resource::Render()
{
	_quad->Render();
}

void Bro_Resource::SetActive(bool isActive)
{
	_isActive = isActive;
}
