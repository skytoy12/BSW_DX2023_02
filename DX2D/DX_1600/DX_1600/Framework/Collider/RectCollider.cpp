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
    _vertices.push_back(temp); // ���� ��

    temp.pos = XMFLOAT3(halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // ������ ��

    temp.pos = XMFLOAT3(halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // ������ �Ʒ�

    temp.pos = XMFLOAT3(-halfSize.x, -halfSize.y, 0.0f);
    _vertices.push_back(temp); // ���� �Ʒ�

    temp.pos = XMFLOAT3(-halfSize.x, halfSize.y, 0.0f);
    _vertices.push_back(temp); // ���� ��
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

RectCollider::OBBRectinfo RectCollider::GetOBBInfo()
{
    OBBRectinfo info;

    info.worldPos = _transform->GetWorldPosition();

    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix, _transform->GetMatrix());

    info.direction[0] = { matrix._11, matrix._12 };
    info.direction[1] = { matrix._21, matrix._22 };

    info.length[0] = GetWorldSize().x * 0.5f;
    info.length[1] = GetWorldSize().y * 0.5f;

    return info;
}

bool RectCollider::Block(shared_ptr<RectCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;
    Vector2 dir = moveable->GetTransform()->GetWorldPosition() - _transform->GetWorldPosition();
    Vector2 sum = moveable->GetWorldSize() * 0.5f + GetWorldSize() * 0.5f;
    Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

    Vector2 fixedPos = moveable->GetTransform()->GetPos();

    dir.Nomallize();

    if (overlap.x > overlap.y)
    {
        if (dir.y < 0.0f)
            dir.y = -1.0f;
        else if (dir.y > 0.0f)
            dir.y = 1.0f;

        fixedPos.y += dir.y * overlap.y;
    }
    else
    {
        if (dir.x < 0.0f)
            dir.x = -1.0f;
        else if (dir.x > 0.0f)
            dir.x = 1.0f;

        fixedPos.x += dir.x * overlap.x;
    }

    moveable->GetTransform()->SetPosition(fixedPos);
    return true;
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
        if (info.top + other->GetWorldRadius() > other->GetTransform()->GetWorldPosition().y
            && info.bottom - other->GetWorldRadius() < other->GetTransform()->GetWorldPosition().y)
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

bool RectCollider::Block(shared_ptr<CircleCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;
    Vector2 virtualHalfSize = Vector2(moveable->GetWorldRadius(), moveable->GetWorldRadius());
    Vector2 dir = moveable->GetTransform()->GetWorldPosition() - _transform->GetWorldPosition();
    Vector2 sum = virtualHalfSize + GetWorldSize() * 0.5f;
    Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

    Vector2 fixedPos = moveable->GetTransform()->GetPos();

    dir.Nomallize();

    if (overlap.x > overlap.y)
    {
        if (dir.y < 0.0f)
            dir.y = -1.0f;
        else if (dir.y > 0.0f)
            dir.y = 1.0f;

        fixedPos.y += dir.y * overlap.y;
    }
    else
    {
        if (dir.x < 0.0f)
            dir.x = -1.0f;
        else if (dir.x > 0.0f)
            dir.x = 1.0f;

        fixedPos.x += dir.x * overlap.x;
    }

    moveable->GetTransform()->SetPosition(fixedPos);
    return true;
}
