#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: Collider(),
    _radius(radius)
{
    _type = Collider::ColliderType::CIRCLE;
    CreateVertices();
    CreatData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
    _transform->Update();
}

void CircleCollider::Render()
{
    _vertexBuffer->Set(0);

    _transform->SetBuffer(0); // vs

    _colorBuffer->SetPSBuffer(0); // ps

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}


void CircleCollider::CreateVertices()
{
    Vertex temp;
 
    for (int i = 0; i < 41; i++)
    {
        temp.pos = XMFLOAT3(_radius * cos(Angle(i * 9)), _radius * sin(Angle(i * 9)), 0.0f);
        _vertices.push_back(temp);
    }

 
}


bool CircleCollider::IsCollision(Vector2 pos)
{
    float distance = (_transform->GetWorldPosition() - pos).Length();
    return distance < GetWorldRadius();
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    Vector2 center1 = _transform->GetWorldPosition();
    Vector2 center2 = other->_transform->GetWorldPosition();

    float distance = (center1 - center2).Length();
    return distance < GetWorldRadius() + other->GetWorldRadius();
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
    return other->IsCollision(shared_from_this());
}
