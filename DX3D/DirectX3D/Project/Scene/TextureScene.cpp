#include "Framework.h"
#include "TextureScene.h"


TextureScene::TextureScene()
{
	quad = new Quad();
}

TextureScene::~TextureScene()
{
	delete quad;
}

void TextureScene::Update()
{
	quad->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	quad->Render();
}

void TextureScene::PostRender()
{
}
