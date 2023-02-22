#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count, UINT offset, bool instance)
: _stride(stride)
, _count(count)
, _offset(offset)
, _isInstance(instance)
, _data(data)
{
	if (instance)
		CreateVertexBuffer_Instance(data);
	else
		CreateVertexBuffer(data);
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::IASet(int slot)
{
    Update();
    DC->IASetVertexBuffers(slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
}

void VertexBuffer::Update()
{
	if (_isInstance == false)
		return;

	DC->Map(_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);
	memcpy(_subResource.pData, _data, (size_t)(_count * _stride));
	DC->Unmap(_vertexBuffer.Get(), 0);
}

void VertexBuffer::CreateVertexBuffer(void* data)
{
    // Vertex ¹öÆÛ : Vertex
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _stride * _count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    DEVICE->CreateBuffer(&bd, &initData, _vertexBuffer.GetAddressOf());
}

void VertexBuffer::CreateVertexBuffer_Instance(void* data)
{	
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = _stride * _count;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	DEVICE->CreateBuffer(&bd, &initData, _vertexBuffer.GetAddressOf());
}
