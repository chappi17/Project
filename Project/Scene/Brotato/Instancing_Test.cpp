#include "framework.h"
#include "Instancing_Test.h"

Instancing_Test::Instancing_Test()
{
	wstring path = (L"Effect/");
	_quad = make_shared<Quad>(path + L"resource.png");
	_quad->SetVertexShader(ADD_VS(L"InstanceVertexShader"));
	_quad->SetPixelShader(ADD_PS(L"InstancePixelShader"));

	_instanceDataes.resize(1);


	for (auto& data : _instanceDataes)
	{
		Transform transform;
		transform.GetPos() = { CENTER_X,CENTER_Y };
		transform.SetSRT();

		data.matrix = XMMatrixTranspose(*transform.GetMatrix());
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(InstanceData), 1, 0, true);
}

Instancing_Test::~Instancing_Test()
{
}

void Instancing_Test::Update()
{

}

void Instancing_Test::Render()
{
	_instanceBuffer->IASet(1);
	_quad->SetRender();

	DC->DrawIndexedInstanced(6, 100, 0, 0, 0);

	_resource->Render();

}
