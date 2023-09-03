#pragma once
class Cube : public Transform
{
public:
	Cube(Vector4 color);
	~Cube();

    void Update();
    void Render();

    void CreateMesh(Vector4 color);
    void CreateNormal();


private:
    Material* material;
    Mesh*     mesh;


    MatrixBuffer* worldBuffer;


    vector<VertexColorNormal> vertices;
    vector<UINT>         indices;

    static int count;
};

