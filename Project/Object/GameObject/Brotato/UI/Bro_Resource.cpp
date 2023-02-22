#include "framework.h"
#include "Bro_Resource.h"

Bro_Resource::Bro_Resource()
{
	wstring path = (L"Effect");
	_quad = make_shared<Quad>(path + L"resource.png");
	_quad->SetVertexShader(ADD_VS(L"InstanceVertexShader"));
	_quad->SetPixelShader(ADD_PS(L"InstancePixelShader"));

	_instanceDataes.resize(10);

	for (auto& data : _instanceDataes)
	{
		Transform transform;
		transform.GetPos() = { CENTER_X,CENTER_Y };
		transform.SetSRT();

		data.matrix = XMMatrixTranspose(*transform.GetMatrix());
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDataes.data(), sizeof(InstanceData), 10, 0, true);
}

Bro_Resource::~Bro_Resource()
{
}

void Bro_Resource::Update()
{

}

void Bro_Resource::Render()
{
	if (IsActive() == false)
		return;

	_instanceBuffer->IASet(1);
	_quad->SetRender();

	DC->DrawIndexedInstanced(6, 100, 0, 0, 0);
}

void Bro_Resource::SetActive(bool isActive)
{
	_isActive = isActive;
}
