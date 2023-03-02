#include "framework.h"
#include "Instancing_Test.h"

Instancing_Test::Instancing_Test()
{
	_bar = make_shared<HPBar>();
	_bar->GetTransform()->GetPos() = { CENTER_X,CENTER_Y };
}

Instancing_Test::~Instancing_Test()
{
}

void Instancing_Test::Update()
{
	_bar->Update();
}

void Instancing_Test::Render()
{
	_bar->Render();
}
