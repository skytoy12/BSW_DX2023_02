#pragma once
class Scene
{
public :
	enum State
	{
		FIRST,
		SECOND,
		THIRD,
		BOSS,
		NONE
	};

	Scene() {}
	virtual ~Scene() {}

	virtual void Init() {};
	virtual void End() {};

	virtual void Update() abstract;
	virtual void Render() abstract;

	virtual void PostRender() abstract;
	virtual void PreRender()  abstract;

	void SetType(State type) { type = type; }

protected :
	State type = NONE;
};

