#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
	: _size(size), Collider(Collider::ColliderType::RECT)
{
    CreateVertices();
    Collider::CreatData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    Collider::Update();
}

void RectCollider::Render()
{
    Collider::Render();
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
    AABBRectInfo info = GetAABBInfo();
    if (pos.x < info.left || pos.x > info.right)
        return false;
    if (pos.y > info.top || pos.y < info.bottom)
        return false;

    return true;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    AABBRectInfo info = GetAABBInfo();
    AABBRectInfo otherInfo = other->GetAABBInfo();
    if (info.right > otherInfo.left && info.left < otherInfo.right)
    {
        if (info.bottom < otherInfo.top && info.top > otherInfo.bottom)
            return true;
    }
    return false;
}

RectCollider::AABBRectInfo RectCollider::GetAABBInfo()
{
    AABBRectInfo result;
    result.left = _transform->GetWorldPosition().x - (GetWorldSize().x * 0.5);
    result.right = _transform->GetWorldPosition().x + (GetWorldSize().x * 0.5);
    result.top = _transform->GetWorldPosition().y + (GetWorldSize().y * 0.5);
    result.bottom = _transform->GetWorldPosition().y - (GetWorldSize().y * 0.5);

    return result;
}

void RectCollider::Block(shared_ptr<RectCollider> moveable)
{
    if (!IsCollision(moveable))
        return;
    Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();
    Vector2 Length = moveableCenter - blockCenter;

    float moveableHalfSizeX = moveable->GetWorldSize().x * 0.5f;
    float moveableHalfSizeY = moveable->GetWorldSize().y * 0.5f;
    float blockHalfSizeX = GetWorldSize().x * 0.5f;
    float blockHalfSizeY = GetWorldSize().y * 0.5f;

    if (blockCenter.x + blockHalfSizeX > moveableCenter.x - moveableHalfSizeX && blockCenter.x - blockHalfSizeX < moveableCenter.x + moveableHalfSizeX && blockCenter.y < moveableCenter.y - moveableHalfSizeY)
    {
        float scala = abs((moveableHalfSizeY + blockHalfSizeY) - abs(moveableCenter.y - blockCenter.y));
        moveable->GetTransform()->AddVector2({ 0.0f, scala });
    }
    else if (blockCenter.x + blockHalfSizeX > moveableCenter.x - moveableHalfSizeX && blockCenter.x - blockHalfSizeX < moveableCenter.x + moveableHalfSizeX && blockCenter.y > moveableCenter.y + moveableHalfSizeY)
    {
        float scala = abs((moveableHalfSizeY + blockHalfSizeY) - abs(moveableCenter.y - blockCenter.y));
        moveable->GetTransform()->AddVector2({ 0.0f, -scala });
    }
    else if (blockCenter.y - blockHalfSizeY < moveableCenter.y + moveableHalfSizeY && blockCenter.y + blockHalfSizeY > moveableCenter.y - moveableHalfSizeY && blockCenter.x < moveableCenter.x - moveableHalfSizeX)
    {
        float scala = abs((moveableHalfSizeX + blockHalfSizeX) - abs(moveableCenter.x - blockCenter.x));
        moveable->GetTransform()->AddVector2({ scala, 0.0f });
    }
    else if (blockCenter.y - blockHalfSizeY < moveableCenter.y + moveableHalfSizeY && blockCenter.y + blockHalfSizeY > moveableCenter.y - moveableHalfSizeY && blockCenter.x > moveableCenter.x + moveableHalfSizeX)
    {
        float scala = abs((moveableHalfSizeX + blockHalfSizeX) - abs(moveableCenter.x - blockCenter.x));
        moveable->GetTransform()->AddVector2({ -scala, 0.0f });
    }
    else
        return;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
    AABBRectInfo info = GetAABBInfo();

    Vector2 leftTop = Vector2(info.left, info.top);
    Vector2 leftBottom = Vector2(info.left, info.bottom);
    Vector2 rightTop = Vector2(info.right, info.top);
    Vector2 rightBottom = Vector2(info.right, info.bottom);

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom) ||
        other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;
    if (info.right > other->GetTransform()->GetWorldPosition().x && info.left < other->GetTransform()->GetWorldPosition().x)
    {
        if (info.top - other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().y
            && info.bottom + other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().y)
            return true;
    }
    if (info.bottom < other->GetTransform()->GetWorldPosition().y && info.top > other->GetTransform()->GetWorldPosition().y)
    {
        if (info.left - other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().x
            && info.right + other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().x)
            return true;
    }
    return false;
}
