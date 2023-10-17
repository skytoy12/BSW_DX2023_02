#include "Framework.h"
#include "ModelClip.h"

ModelClip::ModelClip()
{
}

ModelClip::~ModelClip()
{
	for (pair<string, KeyFrame*> frame : keyFrames)
		delete frame.second;

	keyFrames.clear();
}

KeyFrame* ModelClip::GetKeyFrames(string name)
{
	if (keyFrames.count(name) == 0)
		return nullptr;

	return keyFrames[name];
}
