#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
	_type = ColliderType::CIRCLE;
	CreateVertices();
}

CircleCollider::CircleCollider(float radius)
	: _radius(radius)
{
	_type = ColliderType::CIRCLE;
	CreateVertices();
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::IsCollision(Vector2 pos)
{
	if ((this->GetTransform()->GetWorldPos() - pos).Length() <= (this->GetWorldRadius()))
	{
		return true;
	}
	return false;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	if ((this->GetTransform()->GetWorldPos() - other->GetTransform()->GetWorldPos()).Length() <= (this->GetWorldRadius() + other->GetWorldRadius()))
	{
		return true;
	}
	return false;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> rect)
{
	return rect->IsCollision(shared_from_this());
}

bool CircleCollider::Block(shared_ptr<CircleCollider> other)
{
	if (this->IsCollision(other))
	{
		Vector2 dir = other->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
		float length = dir.Length();
		float radiusSum = other->GetWorldRadius() + GetWorldRadius();

		float overlap = radiusSum - length;
		dir.Normallize();

		other->GetTransform()->GetPos() += dir * overlap;
	
		return true;
	}
	return true;
}

bool CircleCollider::IsCollision_OBB(shared_ptr<CircleCollider> circle)
{
	return IsCollision(circle);
}

bool CircleCollider::IsCollision_OBB(shared_ptr<RectCollider> other)
{
	return other->IsCollision_OBB(shared_from_this());
}

float CircleCollider::GetWorldRadius()
{
	float scaleX = _transform->GetScale().x;
	float scaleY = _transform->GetScale().y;

	return _radius * __max(scaleX, scaleY);
}

void CircleCollider::CreateVertices()
{
	UINT vertexCount = 36;

	for (int i = 0; i < 37; i++)
	{
		Vertex_Bagic vertex;
		vertex.pos.x = _radius * cos((2 * PI * i) / 36);
		vertex.pos.y = _radius * sin((2 * PI * i) / 36);
		_vertices.push_back(vertex);
	}

	Collider::CreateData();

	_colorBuffer->_data.color = { 0.0f,255.0f,0.0f,1.0f };
}
