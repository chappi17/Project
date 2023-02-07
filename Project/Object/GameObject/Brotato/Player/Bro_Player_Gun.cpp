#include "framework.h"
#include "Bro_Player_Gun.h"

Bro_Player_Gun::Bro_Player_Gun()
{
	_transform = make_shared<Transform>();
	_collider = make_shared<RectCollider>(Vector2(35.0f, 10.0f));

	_radious = make_shared<CircleCollider>(300);
	wstring path = (L"Gun/");
	_quad = make_shared<Quad>(path + L"gun.png");
	_quad->GetTransform()->GetScale().x *= 0.05f;
	_quad->GetTransform()->GetScale().y *= 0.05f;

	_quad->GetTransform()->SetParent(_transform);
	_collider->GetTransform()->SetParent(_transform);
	_radious->GetTransform()->SetParent(_transform);

	//_transform->GetPos() = { CENTER_X,CENTER_Y };
}

Bro_Player_Gun::~Bro_Player_Gun()
{
}

void Bro_Player_Gun::Update()
{

	_transform->Update();
	_collider->Update();
	_radious->Update();
	_quad->Update();

}

void Bro_Player_Gun::Render()
{	
	_collider->Render();
	_radious->Render();
	_quad->Render();
}

void Bro_Player_Gun::Target(vector<shared_ptr<Bro_Monster>>& monsters)
{
	for (const auto& monster : monsters)
	{
		if (_radious->IsCollision(monster->GetCollider()))
		{
			Vector2 direction = monster->GetCollider()->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
			float angle = direction.Angle();
			_quad->GetTransform()->SetAngle(angle);
			_collider->GetTransform()->SetAngle(angle);
		}
	}
}

bool Bro_Player_Gun::IsCollision(shared_ptr<Collider> _col)
{
	return _collider->IsCollision(_col);
}
