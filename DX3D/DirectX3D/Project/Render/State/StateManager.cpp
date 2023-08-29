#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
}

StateManager::~StateManager()
{
	delete samplerState;
}

void StateManager::CreateSamplerState()
{
	samplerState = new SamplerState();
}
