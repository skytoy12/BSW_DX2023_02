#include "Framework.h"
#include "Cube.h"
int Cube::count = 0;
Cube::Cube(Vector4 color)
{
    material = new Material(L"Tutorial");


    CreateMesh(color);

    worldBuffer = new MatrixBuffer();

    count++;

    label = "Cube" + to_string(count);
}

Cube::~Cube()
{
    delete mesh;
    delete material;
    delete worldBuffer;
}

void Cube::Update()
{
    Transform::Update();

    worldBuffer->SetData(world);
}

void Cube::Render()
{
    material->SetMaterial();
        mesh->SetMesh();

    worldBuffer->SetVSBuffer(0);

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Cube::CreateMesh(Vector4 color)
{
    vertices =
    {
        VertexColor({ -1.0f, +1.0f, -1.0f }, color),
        VertexColor({ +1.0f, +1.0f, -1.0f }, color),
        VertexColor({ -1.0f, -1.0f, -1.0f }, color),
        VertexColor({ +1.0f, -1.0f, -1.0f }, color),

        VertexColor({ -1.0f, +1.0f, +1.0f }, color),
        VertexColor({ +1.0f, +1.0f, +1.0f }, color),
        VertexColor({ -1.0f, -1.0f, +1.0f }, color),
        VertexColor({ +1.0f, -1.0f, +1.0f }, color),
    };

    //VertexBuffer

    // IndexBuffer
  
    indices =
    {
        //Front
        0, 1, 2,
        2, 1, 3,

        //Right
        1, 5, 3,
        3, 5, 7,

        //Top
        0, 4, 1,
        1, 4, 5,

        //Left
        4, 0, 6,
        6, 0, 2,

        //Back
        5, 4, 7,
        7, 4, 6,

        //Bottom
        2, 3, 6,
        6, 3, 7
    };

    mesh = new Mesh(vertices, indices);
}

void Cube::Debug()
{
    if (ImGui::BeginMenu(label.c_str()))
    {
        ImGui::DragFloat3("Scale", (float*)&scale,             0.01f,      0.01f,    100.0f);
        // ImGui::DragFloat3("Lotation", (float*)&rotation,       0.01f,    -XM_2PI,    XM_2PI);

        ImGui::SliderAngle("RotationX", &rotation.x);
        ImGui::SliderAngle("RotationY", &rotation.y);
        ImGui::SliderAngle("RotationZ", &rotation.z);

        ImGui::DragFloat3("Translation", (float*)&translation, 0.01f, -WIN_WIDTH, WIN_WIDTH);
        ImGui::EndMenu();
    }
}
