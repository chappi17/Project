#pragma once
class Button
{
public:
	struct TextInfo
	{
		wstring text = L"";
		RECT rect;
		float size = 20.0f;
		XMFLOAT4 color = { 1,1,1,1 };
	};

	enum State
	{
		NONE,
		HOVER,
		CLICK
	};

	Button(wstring path);
	Button(Vector2 size);
	~Button();

	void Update();
	void PostRender();

	void SetPostion(Vector2 pos);
	void SetScale(Vector2 scale);

	void SetEvent(CallBack callBack) { _callBack = callBack; }
	void SetEvent_INT(CallBack_1 callBack) { _callBack_int = callBack; }
	void SetEvent_String(std::function<void(string)> callBack) { _callBack_string = callBack; }

	void SetText(TextInfo info) { _textInfo = info; }

	void SetParent(shared_ptr<Transform> transform);

	Vector2 LeftTop() { return _collider->LeftTop(); }
	Vector2 RightBottom() { return _collider->RightBottom(); }

private:
	State _state;

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _collider;
	shared_ptr<ButtonInfoBuffer> _buttonInfoBuffer;

	TextInfo _textInfo;

	CallBack _callBack;
	CallBack_1 _callBack_int;
	std::function<void(string)> _callBack_string;
};

