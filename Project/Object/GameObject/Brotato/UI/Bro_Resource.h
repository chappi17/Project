#pragma once
class Bro_Resource
{
public:

	struct InstanceData
	{
		XMMATRIX matrix;
	};

	Bro_Resource();
	~Bro_Resource();

	void Update();
	void Render();

	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }

	shared_ptr<Quad> GetQuad() {return _quad;}
	shared_ptr<Transform> GetTransform() { return _transform; }
	vector<InstanceData> GetDatas() {return  _instanceDataes; }

private:
	bool _isActive = true;
	shared_ptr<Quad> _quad;

	vector<InstanceData> _instanceDataes;  // ���� ��ġ ������ �� �׸��� �нż� �ϴ°�
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<Transform> _transform;
};

