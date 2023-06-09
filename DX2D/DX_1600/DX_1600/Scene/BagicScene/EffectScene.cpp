#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/CupHead/GreenExplosion.png", Vector2(4, 4), Vector2(100, 100));
	SOUND->Add("BGM1", "Resource/CupHead/Sound/BGM.mp3", true);
	SOUND->Play("BGM1");
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT_PLAY("Hit", MOUSE_POS);
	}
}

void EffectScene::Render()
{

}
