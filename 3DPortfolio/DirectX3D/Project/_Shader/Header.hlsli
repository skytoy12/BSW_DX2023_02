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

cbuffer LightDirection : register(b0)
{
    float3 lightDirection;
    float padding;
    float4 ambientLight;
}

cbuffer MaterialBuffer : register(b1)
{
    float4 mDiffuse;
    float4 mSpecular;
    float4 mAmbeint;
    float4 mEmissive;
    
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
    int hasAlphaMap;
    
    float shininess;
}

struct Frame
{
    int   clip;
    uint  curFrame;
    float time;
    float speed;
};

struct Motion
{
    float takeTime;
    float tweenTime;
    float runningTime;
    float padding2;
    
    Frame cur, next;
};

cbuffer FrameBuffer : register(b3)
{
    Motion motion;
}

Texture2DArray transformMap : register(t0);

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
    float4 pos    : POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
    float4 pos     : POSITION;
    float2 uv      : UV;
    float3 normal  : NORMAL;
    float3 tangent : TANGENT;
};

struct VertexTextureNormalTangentAlpha
{
    float4 pos     : POSITION;
    float2 uv      : UV;
    float3 normal  : NORMAL;
    float3 tangent : TANGENT;
    float4 alpha   : ALPHA;
};

struct VertexTextureNormalTangentBlend
{
    float4 pos     : POSITION;
    float2 uv      : UV;
    float3 normal  : NORMAL;
    float3 tangent : TANGENT;
    float4 indices : BLENDINDICES;
    float4 weights : BLENDWEIGHTS;
};

Texture2D  diffusemap : register(t0);
Texture2D specularmap : register(t1);
Texture2D   normalmap : register(t2);

SamplerState    samp : register(s0);