#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius), Collider(Collider::ColliderType::CIRCLE)
{
    CreateVertices();
    Collider::CreatData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
    Collider::Update();
}

void CircleCollider::Render()
{
    Collider::Render();
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

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    if (isObb)
        return OBB_Collision(other);
    return AABB_Collision(other);
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    if (isObb)
        return OBB_Collision(other);
    return AABB_Collision(other);
}

bool CircleCollider::AABB_Collision(shared_ptr<RectCollider> other)
{
    return other->IsCollision(shared_from_this());
}

bool CircleCollider::AABB_Collision(shared_ptr<CircleCollider> other)
{
    Vector2 center1 = _transform->GetWorldPosition();
    Vector2 center2 = other->_transform->GetWorldPosition();

    float distance = (center1 - center2).Length();
    return distance < GetWorldRadius() + other->GetWorldRadius();
}

bool CircleCollider::OBB_Collision(shared_ptr<RectCollider> other)
{
    return other->IsCollision(shared_from_this());
}

bool CircleCollider::OBB_Collision(shared_ptr<CircleCollider> other)
{
    return AABB_Collision(other);
}

bool CircleCollider::Block(shared_ptr<CircleCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;
    Vector2 moveableCenter = moveable->GetTransform()->GetWorldPosition();
    Vector2 blockCenter = GetTransform()->GetWorldPosition();
    Vector2 dir = moveableCenter - blockCenter;

    float moveableRaduius = moveable->GetWorldRadius();
    float blockRaduius = GetWorldRadius();

    float scalar = abs((moveableRaduius + blockRaduius) - dir.Length());
    dir.Nomallize();

    moveable->GetTransform()->AddVector2(dir * scalar * DELTA_TIME);

    return true;
}

bool CircleCollider::Block(shared_ptr<RectCollider> moveable)
{
    if (!IsCollision(moveable))
        return false;


    Vector2 dir = moveable->GetTransform()->GetWorldPosition() - _transform->GetWorldPosition();
    Vector2 sum = moveable->GetWorldSize() * 0.5f + Vector2(GetWorldRadius(), GetWorldRadius());
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