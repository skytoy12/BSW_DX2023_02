#pragma once
class Cube
{
public:
	Cube();
	~Cube();

    void Update();
    void Render();

    void CreateMesh();

    void Debug();

private:
    Material* material;
    Mesh*     mesh;


    MatrixBuffer* worldBuffer;


    vector<VertexColor> vertices;
    vector<UINT>         indices;

    //SRT

    XMFLOAT3 scale       = { 1.0f, 1.0f, 1.0f };
    XMFLOAT3 rotation    = { 0.0f, 0.0f, 0.0f };
    XMFLOAT3 translation = { 0.0f, 0.0f, 0.0f };

    XMMATRIX S;
    XMMATRIX R;
    XMMATRIX T;

    XMMATRIX world;
};

