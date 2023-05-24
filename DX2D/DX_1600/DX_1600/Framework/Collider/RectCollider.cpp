#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	:Collider(), _size(size)
{
    _type = Collider::ColliderType::RECT;
    CreateVertices();
    CreatData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _transform->Update();
}

void RectCollider::Render()
{
    _vertexBuffer->Set(0);

    _transform->SetBuffer(0);

    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}



void RectCollider::CreateVertices()
{
    Vertex temp;
    Vector2 halfSize;
    halfSize.x = (_size.x) * 0.5f;
    halfSize.y = (_size.y) * 0.5f;

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 위

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 위

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // 오른쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 아래

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // 왼쪽 위
}

bool RectCollider::IsCollision(Vector2 pos)
{
    if (pos.x < WorldLeft() || pos.x > WorldRight())
        return false;
    if (pos.y > WorldTop() || pos.y < WorldBottom())
        return false;

    return true;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    if (WorldRight() > other->WorldLeft() && WorldLeft() < other->WorldRight())
    {
        if (WorldBottom() < other->WorldTop() && WorldTop() > other->WorldBottom())
            return true;
    }
    return false;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    Vector2 leftTop = Vector2(WorldLeft(), WorldTop());
    Vector2 leftBottom = Vector2(WorldLeft(), WorldBottom());
    Vector2 rightTop = Vector2(WorldRight(), WorldTop());
    Vector2 rightBottom = Vector2(WorldRight(), WorldBottom());

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom) ||
        other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;
    if (WorldRight() > other->GetTransform()->GetWorldPosition().x && WorldLeft() < other->GetTransform()->GetWorldPosition().x)
    {
        if (WorldTop() - other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().y
            && WorldBottom() + other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().y)
            return true;
    }
    if (WorldBottom() < other->GetTransform()->GetWorldPosition().y && WorldTop() > other->GetTransform()->GetWorldPosition().y)
    {
        if (WorldLeft() - other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().x
            && WorldRight() + other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().x)
            return true;
    }
    return false;
}
