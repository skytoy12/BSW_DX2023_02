#include "framework.h"
#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;
SoundManager::SoundManager()
{
	_palyerattacksound = "(플레이어가 공격하는 소리)";
	_archerattacksound = "(궁수가 공격하는 소리)";
	_knightattacksound = "(기사가 공격하는 소리)";
	_magicianattacksound = "(마법사가 공격하는 소리)";
	_monsterattacksound = "(몬스터가 공격하는 소리)";
	_Bossattacksound = "(보스가 공격하는 소리)";
	_tauntsound = "(기사가 도발하는 소리)";
	_fireballsound = "(마법사가 파이어볼을 쏘는 소리)";
}

SoundManager::~SoundManager()
{
}
