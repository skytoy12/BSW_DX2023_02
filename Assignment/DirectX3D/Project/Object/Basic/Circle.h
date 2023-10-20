#pragma once
class Circle : public Transform
{
public :
    Circle(Vector4 color, float radius);
    ~Circle();

    void Update();
    void Render();

    float Ridan(float value) { return value * XM_PI / 180; }

    void CreateMesh(Vector4 color, float radius);
    void CreateNormal();
private :
    Material* material;
    Mesh* mesh;


    MatrixBuffer* worldBuffer;


    vector<VertexColorNormal> vertices;
    vector<UINT>         indices;
};

