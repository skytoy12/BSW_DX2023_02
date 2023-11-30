#include "Framework.h"
#include "Mesh.h"

Mesh::~Mesh()
{
	delete vertexBuffer;

	if(indexBuffer)
		delete indexBuffer;	
}

void Mesh::SetMesh(D3D11_PRIMITIVE_TOPOLOGY type)
{
	vertexBuffer->IASetBuffer(type);

	if(indexBuffer)
		indexBuffer->IASetBuffer();	
}


