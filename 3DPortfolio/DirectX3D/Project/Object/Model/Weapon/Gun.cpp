#include "Framework.h"
#include "Gun.h"


Gun::Gun(string file)
	: Model(file)
{
	Model::SetLabel(file);
}

Gun::~Gun()
{
}

void Gun::Update()
{
	Model::Update();
}

void Gun::Render()
{
	Model::Render();
}

void Gun::Debug()
{
	Model::Debug();
	Model::GetReader()->GetMaterials()[0]->Debug();
}
