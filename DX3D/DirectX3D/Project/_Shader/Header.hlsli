cbuffer World : register(b0)
{
    matrix world;
};

cbuffer View : register(b1)
{
    matrix view;
    matrix invView;
};

cbuffer Proj : register(b2)
{
    matrix proj;
};

cbuffer LightDirection : register(b3)
{
    float3 lightDirection;
    float padding;
}

struct VertexColor
{
    float4 pos   : POSITION;
    float4 color : COLOR;
};

struct VertexColorNormal
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
};

struct VertexTexture
{
    float4 pos : POSITION;
    float2 uv  : UV;
};

struct VertexTextureNormal
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
};

Texture2D diffusemap : register(t0);
SamplerState    samp : register(s0);