#include "Framework.h"
#include "TextureScene.h"


TextureScene::TextureScene()
{
	//quad = new Quad();
	box = new Box();
}

TextureScene::~TextureScene()
{
	//delete quad;
	delete box;
}

void TextureScene::Update()
{
	//quad->Update();
	box->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	//quad->Render();
	box->Render();
}

void TextureScene::PostRender()
{
}
