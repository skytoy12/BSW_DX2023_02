#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;

public:
	StateManager();
	~StateManager();

	void CreateSamplerState();
private:
	SamplerState* samplerState = nullptr;

};


