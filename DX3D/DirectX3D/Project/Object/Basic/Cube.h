#pragma once
class Cube
{
public:
	Cube();
	~Cube();

    void Update();
    void Render();

private:
    //Shader -> Material
    VertexShader* vertexShader;
     PixelShader* pixelShader;

    // Vertex, Index -> Mesh
    VertexBuffer* vertexBuffer;
     IndexBuffer* indexBuffer;


    MatrixBuffer* worldBuffer;


    vector<VertexColor> vertices;
    vector<UINT>    indices;
};

