#pragma once
class Quad
{
public:
	Quad(wstring file);
	Quad(wstring file, Vector2 size);
	virtual ~Quad();

	virtual void Update();
	virtual void Render();

	void SetVertexShader(shared_ptr<VertexShader> vs) { _vs = vs; }
	void SetPixelShader(shared_ptr<PixelShader> ps) { _ps = ps; }

	Vector2 GetSize() { return _size; }
	Vector2 GetImage() { return _srv->GetSize(); }

	void SetLeftRight_leftRightBuffer(int leftRight);

	shared_ptr<Transform> GetTransform() { return _transform; }

protected:
	void CreateVertricesAndIndices();
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	vector<Vertex_UV> _vertices;
	vector<UINT> _indices;

	shared_ptr<VertexBuffer> _vBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	Vector2 _size = { 1.0f,1.0f };
	shared_ptr<Transform> _transform;

	shared_ptr<SRV> _srv; 

	shared_ptr<LeftRightBuffer> _leftRightBuffer;


	// 컴포넌트 패턴 -> 유니티의 대표적인 디자인패턴
	// - 부품처럼 갖다 쓰는 형식
};

