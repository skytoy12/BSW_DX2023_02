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

    info.direction[0].Nomallize();
    info.direction[1].Nomallize();

    info.length[0] = GetWorldSize().x * 0.5f;
    info.length[1] = GetWorldSize().y * 0.5f;

    return info;
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

bool RectCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    if (isObb)
        return OBB_Collision(other);
    return AABB_Collision(other);
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    if (isObb)
        return OBB_Collision(other);
    return AABB_Collision(other);
}

bool RectCollider::AABB_Collision(shared_ptr<CircleCollider> other)
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

bool RectCollider::AABB_Collision(shared_ptr<RectCollider> other)
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

bool RectCollider::OBB_Collision(shared_ptr<RectCollider> other)
{
    OBBRectinfo infoA = GetOBBInfo();
    OBBRectinfo infoB = other->GetOBBInfo();

    Vector2 aToB = infoB.worldPos - infoA.worldPos;

    // n : normal... 길이가 1인 벡터
    // e : edge... 모서리
    Vector2 nea1 = infoA.direction[0];
    Vector2 ea1 = infoA.direction[0] * infoA.length[0];
    Vector2 nea2 = infoA.direction[1];
    Vector2 ea2 = infoA.direction[1] * infoA.length[1];

    Vector2 neb1 = infoB.direction[0];
    Vector2 eb1 = infoB.direction[0] * infoB.length[0];
    Vector2 neb2 = infoB.direction[1];
    Vector2 eb2 = infoB.direction[1] * infoB.length[1];

    // nea1축으로 투영
    float length = abs(nea1.Dot(aToB));
    float lengthA = ea1.Length();
    float lengthB = SeparateAxis(nea1, eb1, eb2);

    if (length > lengthA + lengthB)
        return false;

    // nea2 축으로 투영
    length = abs(nea2.Dot(aToB));
    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2, eb1, eb2);

    if (length > lengthA + lengthB)
        return false;

    // neb1 축으로 투영
    length = abs(neb1.Dot(aToB));
    lengthA = SeparateAxis(neb1, ea1, ea2);
    lengthB = eb1.Length();
    
    if (length > lengthA + lengthB)
        return false;

    // neb2 축으로 투영
    length = abs(neb2.Dot(aToB));
    lengthA = SeparateAxis(neb2, ea1, ea2);
    lengthB = eb2.Length();

    if (length > lengthA + lengthB)
        return false;

    return true;
}

bool RectCollider::OBB_Collision(shared_ptr<CircleCollider> other)
{

    OBBRectinfo infoA = GetOBBInfo();
    Vector2 aToB = infoA.worldPos - other->GetTransform()->GetWorldPosition();

    // n : normal... 길이가 1인 벡터
    // e : edge... 모서리
    Vector2 nea1 = infoA.direction[0];
    Vector2 ea1 = infoA.direction[0] * infoA.length[0];
    Vector2 nea2 = infoA.direction[1];
    Vector2 ea2 = infoA.direction[1] * infoA.length[1];

    float radius = sqrt((ea1.Length() * ea1.Length()) + (ea2.Length() * ea2.Length()));
    float angle = GetTransform()->GetAngle();
    Vector2 RightTop = Vector2(GetTransform()->GetWorldPosition().x + radius * cos((float) (angle + (45 * (PI / 180)))), (float)(GetTransform()->GetWorldPosition().y + radius * sin(angle + (45 * (PI / 180)))));
    Vector2 RightBottom = Vector2(GetTransform()->GetWorldPosition().x + radius * cos((float) (angle + (135 * (PI / 180)))), (float)(GetTransform()->GetWorldPosition().y + radius * sin(angle + (135 * (PI / 180)))));
    Vector2 LeftTop = Vector2(GetTransform()->GetWorldPosition().x + radius * cos((float) (angle + (225 * (PI / 180)))), (float)(GetTransform()->GetWorldPosition().y + radius * sin(angle + (225 * (PI / 180)))));
    Vector2 LeftBottom = Vector2(GetTransform()->GetWorldPosition().x + radius * cos((float) (angle + (315 * (PI / 180)))), (float)(GetTransform()->GetWorldPosition().y + radius * sin(angle + (315 * (PI / 180)))));

    if (other->IsCollision(RightTop) || other->IsCollision(RightBottom) ||
        other->IsCollision(LeftTop) || other->IsCollision(LeftBottom))
        return true;

    float length = abs(nea1.Dot(aToB));
    float lengthA = ea1.Length();
    float lengthB = other->GetWorldRadius();

    if (length > lengthA + lengthB)
        return false;

    length = abs(nea2.Dot(aToB));
    lengthA = ea2.Length();
    lengthB = other->GetWorldRadius();

    if (length > lengthA + lengthB)
        return false;

    // neb1 축으로 투영
    length = abs(Vector2(1.0f, 0.0f).Dot(aToB));
    lengthA = SeparateAxis(Vector2(1.0f, 0.0f), ea1, ea2);
    lengthB = other->GetWorldRadius();

    if (length > lengthA + lengthB)
        return false;

    // neb2 축으로 투영
    length = abs(Vector2(0.0f, 1.0f).Dot(aToB));
    lengthA = SeparateAxis(Vector2(0.0f, 1.0f), ea1, ea2);
    lengthB = other->GetWorldRadius();

    if (length > lengthA + lengthB)
        return false;

    if (!AABB_Collision(other))
        return false;


    return true;
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
