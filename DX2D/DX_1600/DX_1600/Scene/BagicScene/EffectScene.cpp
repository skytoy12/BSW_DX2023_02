#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	EffectManager::GetInstance()->AddEffect("GreenEffect", L"Resource/CupHead/GreenExplosion.png", Vector2(4, 4), Vector2(150, 150));
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT_PLAY("GreenEffect", MOUSE_POS);
	}
}

void EffectScene::Render()
{

}
