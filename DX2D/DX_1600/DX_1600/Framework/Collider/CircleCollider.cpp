#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius)
{
    CreateData();
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

    _transform->SetBuffer(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

void CircleCollider::CreateData()
{
    CreateVertices();
    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

    _vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

    _transform = make_shared<Transform>();
}

void CircleCollider::CreateVertices()
{
    Vertex temp;
 

    temp.pos = XMFLOAT3(0.0f, _radius, 0.0f);
    _vertices.push_back(temp); // 위

    temp.pos = XMFLOAT3(sin(Angle(9)) * _radius, cos(Angle(9)) * _radius, 0.0f);
    _vertices.push_back(temp); 

    temp.pos = XMFLOAT3(sin(Angle(18)) * _radius, cos(Angle(18)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(27)) * _radius, cos(Angle(27)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(36)) * _radius, cos(Angle(36)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(45)) * _radius, cos(Angle(45)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(54)) * _radius, cos(Angle(54)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(63)) * _radius, cos(Angle(63)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(72)) * _radius, cos(Angle(72)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(sin(Angle(81)) * _radius, cos(Angle(81)) * _radius, 0.0f);
    _vertices.push_back(temp);


    temp.pos = XMFLOAT3(_radius, 0.0f, 0.0f);
    _vertices.push_back(temp); // 오른쪽

    temp.pos = XMFLOAT3(cos(Angle(9)) * _radius, -sin(Angle(9)) * _radius, 0.0f);
    _vertices.push_back(temp);      
                                    
    temp.pos = XMFLOAT3(cos(Angle(18)) * _radius, -sin(Angle(18)) * _radius, 0.0f);
    _vertices.push_back(temp);      
                                    
    temp.pos = XMFLOAT3(cos(Angle(27)) * _radius, -sin(Angle(27)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(cos(Angle(36)) * _radius, -sin(Angle(36)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(cos(Angle(45)) * _radius, -sin(Angle(45)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(cos(Angle(54)) * _radius, -sin(Angle(54)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(cos(Angle(63)) * _radius, -sin(Angle(63)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(cos(Angle(72)) * _radius, -sin(Angle(72)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(cos(Angle(81)) * _radius, -sin(Angle(81)) * _radius, 0.0f);
    _vertices.push_back(temp);


    temp.pos = XMFLOAT3(0.0f, -_radius, 0.0f);
    _vertices.push_back(temp); // 아래

    temp.pos = XMFLOAT3(-sin(Angle(9)) * _radius, -cos(Angle(9)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(18)) * _radius, -cos(Angle(18)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(27)) * _radius, -cos(Angle(27)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(36)) * _radius, -cos(Angle(36)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(45)) * _radius, -cos(Angle(45)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(54)) * _radius, -cos(Angle(54)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(63)) * _radius, -cos(Angle(63)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(72)) * _radius, -cos(Angle(72)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-sin(Angle(81)) * _radius, -cos(Angle(81)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-_radius, 0.0f, 0.0f);
    _vertices.push_back(temp); // 왼쪽

    temp.pos = XMFLOAT3(-cos(Angle(9)) * _radius, sin(Angle(9)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(18)) * _radius, sin(Angle(18)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(27)) * _radius, sin(Angle(27)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(36)) * _radius, sin(Angle(36)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(45)) * _radius, sin(Angle(45)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(54)) * _radius, sin(Angle(54)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(63)) * _radius, sin(Angle(63)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(72)) * _radius, sin(Angle(72)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(-cos(Angle(81)) * _radius, sin(Angle(81)) * _radius, 0.0f);
    _vertices.push_back(temp);

    temp.pos = XMFLOAT3(0.0f, _radius, 0.0f);
    _vertices.push_back(temp); // 위
}
