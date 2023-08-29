#include "Framework.h"
#include "TextureScene.h"


TextureScene::TextureScene()
{
	//quad = new Quad();
	cube = new TextureCube();
	cube->SetLabel("cube");
}

TextureScene::~TextureScene()
{
	//delete quad;
	delete cube;
}

void TextureScene::Update()
{
	//quad->Update();
	cube->Update();
}

void TextureScene::PreRender()
{

}

void TextureScene::Render()
{
	//quad->Render();
	cube->Render();
}

void TextureScene::PostRender()
{
	cube->Debug();
}
