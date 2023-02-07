#pragma once
class Collider;
class MatrixBuffer;

class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void SetWorldBuffer(int slot = 0);
	void SetSRT();

	// 꺼지거나, 움직임을 한번에 세팅할 떄만 쓰기... 매트릭스 수정까지 해주는 함수
	void SetPos(Vector2 pos) { _pos = pos; SetSRT(); return; }
	void SetScale(Vector2 scale) { _scale = scale; SetSRT(); return; }
	void SetAngle (float angle) { _angle = angle; SetSRT(); return; }

	Vector2& GetScale();
	Vector2 GetWorldScale();

	// 단순 움직임
	Vector2& GetPos() { return _pos; }
	Vector2 GetWorldPos();
	float& GetAngle();
	float GetWorldAngle();


	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	XMMATRIX* GetMatrix() { return &_srtMatrix; }

private:
	Vector2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;
	Vector2 _pos = { 0.0f, 0.0f };

	XMMATRIX _srtMatrix = XMMatrixIdentity();
	shared_ptr<MatrixBuffer> _worldBuffer;

	shared_ptr<Transform> _parent = nullptr;
};
