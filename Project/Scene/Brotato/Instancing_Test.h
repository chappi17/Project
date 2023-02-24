#pragma once
class Instancing_Test :public Scene
{
public:

	struct InstanceData
	{
		XMMATRIX matrix;
	};

	Instancing_Test();
	~Instancing_Test();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad; // �׸� �ϳ��� ����ְ�
	vector<InstanceData> _instanceDataes;  // ���� ��ġ ������ �� �׸��� �нż� �ϴ°�
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<Transform> _transform;

	shared_ptr<Bro_Resource> _resource;
};