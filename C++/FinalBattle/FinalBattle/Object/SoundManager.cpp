#include "framework.h"
#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;
SoundManager::SoundManager()
{
	_palyerattacksound = "(�÷��̾ �����ϴ� �Ҹ�)";
	_archerattacksound = "(�ü��� �����ϴ� �Ҹ�)";
	_knightattacksound = "(��簡 �����ϴ� �Ҹ�)";
	_magicianattacksound = "(�����簡 �����ϴ� �Ҹ�)";
	_monsterattacksound = "(���Ͱ� �����ϴ� �Ҹ�)";
	_Bossattacksound = "(������ �����ϴ� �Ҹ�)";
	_tauntsound = "(��簡 �����ϴ� �Ҹ�)";
	_fireballsound = "(�����簡 ���̾�� ��� �Ҹ�)";
}

SoundManager::~SoundManager()
{
}
