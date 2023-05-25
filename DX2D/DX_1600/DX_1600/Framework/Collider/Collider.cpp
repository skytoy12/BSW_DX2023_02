#include "framework.h"
#include "Collider.h"

Collider::Collider(ColliderType type)
	:_type(type)
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
    _transform->Update();
}

void Collider::Render()
{
    _vertexBuffer->Set(0);

    _transform->SetBuffer(0);

    _colorBuffer->SetPSBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
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
    }
    case Collider::ColliderType::CIRCLE:
    {
        auto circle = dynamic_pointer_cast<CircleCollider>(col);
        return IsCollision(circle);
    }
    case Collider::ColliderType::RECT:
    {
        auto rect = dynamic_pointer_cast<RectCollider>(col);
        return IsCollision(rect);
        break;
    }
    default:
        return false;
    }
   
}
