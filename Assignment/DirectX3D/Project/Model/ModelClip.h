#pragma once
class ModelClip
{
	friend class ModelAnimation;
	friend class ModelAnimator;
public:
	ModelClip();
	~ModelClip();

	KeyFrame* GetKeyFrames(string name);

private:
	string name = "";

	UINT frameCount = 0;

	float ticksPerSecond = 0.0f;
	float duration = 0.0f;

	unordered_map<string, KeyFrame*> keyFrames = {};
};

