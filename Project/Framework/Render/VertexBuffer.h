#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0, bool instance = false);
	~VertexBuffer();

	void IASet(int slot);
	void Update();

private:
	void CreateVertexBuffer(void* data);
	void CreateVertexBuffer_Instance(void* data);

	Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	bool _isInstance;
	void* _data;
	UINT _stride;
	UINT _offset;
	UINT _count;
};

