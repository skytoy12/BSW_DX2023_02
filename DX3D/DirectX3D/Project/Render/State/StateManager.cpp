#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSamplerState();
	CreateRasterizerState();
	CreateBlendState();
}

StateManager::~StateManager()
{
	delete samplerState;
	delete rasterizerState;
	for (BlendState* blendState : blendStates)
		delete blendState;

	blendStates.clear();
}

void StateManager::CreateSamplerState()
{
	samplerState = new SamplerState();
}

void StateManager::CreateRasterizerState()
{
	rasterizerState = new RasterizerState();
	rasterizerState->SetState();
}

void StateManager::CreateBlendState()
{
	blendStates.push_back(new BlendState());
	blendStates.push_back(new BlendState());
	blendStates.push_back(new BlendState());

	blendStates[1]->Alpha(true);
	blendStates[2]->Additive();
}

void StateManager::AlphaBegin()
{
	blendStates[1]->SetState();
}

void StateManager::AlphaEnd()
{
	blendStates[0]->SetState();
}
