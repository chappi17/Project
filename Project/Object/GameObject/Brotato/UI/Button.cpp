#include "framework.h"
#include "Button.h"

Button::Button(wstring path)
{
	_quad = make_shared<Quad>(path);
	_quad->SetPixelShader(ADD_PS(L"ButtonPixelShader"));
	_collider = make_shared<RectCollider>(_quad->GetSize());
	_collider->GetTransform()->SetParent(_quad->GetTransform());

	_buttonInfoBuffer = make_shared<ButtonInfoBuffer>();
	_buttonInfoBuffer->_data.hover = 0.2f;
	_buttonInfoBuffer->_data.click = 0.5f;
}

Button::Button(Vector2 size)
{
	_quad = nullptr;
	_collider = make_shared<RectCollider>(size);
}

Button::~Button()
{
}

void Button::Update()
{
	if (_quad != nullptr)
	{
		_quad->Update();
		_buttonInfoBuffer->Update();
	}

	_collider->Update();

	if (_collider->IsCollision(mousePos))
	{
		_state = State::HOVER;
		if(_buttonInfoBuffer != nullptr)
			_buttonInfoBuffer->_data.state = static_cast<int>(_state);

		if (KEY_PRESS(VK_LBUTTON))
		{
			_state = State::CLICK;
			_collider->SetRED();
			if (_buttonInfoBuffer != nullptr)
				_buttonInfoBuffer->_data.state = static_cast<int>(_state);
		}

		if (KEY_UP(VK_LBUTTON))
		{
			if(_callBack != nullptr)
				_callBack();
			if (_callBack_int != nullptr)
				_callBack_int(0);
		}
	}
	else
	{
		_state = State::NONE;
		_collider->SetGREEN();
		if (_buttonInfoBuffer != nullptr)
			_buttonInfoBuffer->_data.state = static_cast<int>(_state);
	}
}

void Button::PostRender()
{
	if (_quad != nullptr)
	{
		_buttonInfoBuffer->SetPSBuffer(1);
		_quad->Render();
	}
	_collider->Render();

	if (!_textInfo.text.empty())
	{
		RECT rect = { _collider->LeftTop().x + 23, _collider->LeftTop().y + 13,
		_collider->RightBottom().x , _collider->RightBottom().y + 13 };

		DirectWrite::GetInstance()->RenderText(_textInfo.text, rect, _textInfo.size, L"³ª´®½ºÄù¾î¶ó¿îµåOTF", _textInfo.color);
	}
}
	

void Button::SetPostion(Vector2 pos)
{
	if (_quad != nullptr)
		_quad->GetTransform()->SetPos(pos);
	else
		_collider->GetTransform()->SetPos(pos);
}

void Button::SetScale(Vector2 scale)
{
	if (_quad != nullptr)
		_quad->GetTransform()->SetScale(scale);
	else
		_collider->GetTransform()->SetScale(scale);
}

void Button::SetParent(shared_ptr<Transform> transform)
{
	if (_quad != nullptr)
		_quad->GetTransform()->SetParent(transform);
	else
		_collider->GetTransform()->SetParent(transform);
}
