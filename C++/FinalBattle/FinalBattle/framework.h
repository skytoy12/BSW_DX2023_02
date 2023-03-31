#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

enum class CreatureType
{
	NONE,
	PLAYER,
	MONSTER,
	AGGRO_ABLE
};

#include "Object/SoundManager.h"

#include "Object/Creature.h"
#include "Object/Players/Player.h"
#include "Object/Monsters/Monster.h"
#include "Object/Players/Archer.h"
#include "Object/Players/Knight.h"
#include "Object/Players/Magician.h"
#include "Object/Monsters/Boss.h"
#include "Scene/World.h"