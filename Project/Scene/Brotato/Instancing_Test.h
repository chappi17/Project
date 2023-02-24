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

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad; // 그림 하나만 찍어주고
	vector<InstanceData> _instanceDataes;  // 생성 위치 모조리 찍어서 그림자 분신술 하는거
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<Transform> _transform;

	shared_ptr<Bro_Resource> _resource;
};