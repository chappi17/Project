#include "framework.h"
#include "Bro_Player_Bullet.h"

Bro_Player_Bullet::Bro_Player_Bullet()
{
    _transform = make_shared<Transform>();
    wstring path = (L"Effect/");
    _quad = make_shared<Quad>(path + L"Bullet.png", Vector2{ 60,60 });
    _collider = make_shared<CircleCollider>(10);
    _collider->GetTransform()->GetPos().x = 10;
    _collider->GetTransform()->GetPos().y = -2;

    _quad->GetTransform()->SetParent(_transform);
    _collider->GetTransform()->SetParent(_transform);
    _transform->GetPos() = { CENTER_X,CENTER_Y };
}

Bro_Player_Bullet::~Bro_Player_Bullet()
{
}

void Bro_Player_Bullet::Update()
{ 
 
    if (isActive == false)
        return;

    _transform->GetPos() += _direction * _speed * DELTA_TIME;
    _transform->Update();
    _collider->Update();
    _quad->Update();
}

void Bro_Player_Bullet::Render()
{
    if (isActive == false)
        return;

    _quad->Render();
    _collider->Render();
}

//void Bro_Player_Bullet::Attack(vector<shared_ptr<Bro_Monster>>& monsters)
//{
//    for (auto& monster : monsters)
//    {
//		if (monster->isActive == false)
//		{
//			return;
//		}
//
//        if(_collider->IsCollision(monster->GetCollider()))
//        {
//            isActive = false;
//            monster->isActive = false;
//        }
//    }
//}

void Bro_Player_Bullet::SetDirection(Vector2 dir)
{    
    _direction = dir;
}


