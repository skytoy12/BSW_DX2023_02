#include "framework.h"
#include "Collider.h"

Collider::Collider()
	:_type(Collider::ColliderType::NONE)
{
}

Collider::~Collider()
{
}

void Collider::CreatData()
{
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

    _vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

    _transform = make_shared<Transform>();

    _colorBuffer = make_shared<ColorBuffer>();
    SetGreen();
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
    switch (col->_type)
    {
    case Collider::ColliderType::NONE:
    {
        return false;
        break;
    }
    case Collider::ColliderType::CIRCLE:
    {
        return IsCollision(dynamic_pointer_cast<CircleCollider>(col));
        break;
    }
    case Collider::ColliderType::RECT:
    {
        return IsCollision(dynamic_pointer_cast<RectCollider>(col));
        break;
    }
    default:
        break;
    }
    return false;
}
