#pragma once
class ModelAnimation
{
public:
	ModelAnimation();
	~ModelAnimation();

	void ReadClip(string file, UINT clipIndex = 0);

private:
	ModelReader* reader;

	vector<ModelClip*> clips;
};



