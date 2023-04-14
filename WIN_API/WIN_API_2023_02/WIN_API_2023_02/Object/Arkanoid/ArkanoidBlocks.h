#pragma once
class ArkanoidBlocks
{
public:
	ArkanoidBlocks();
	~ArkanoidBlocks();

	void Update();
	void Render();

private:
	vector<vector<shared_ptr<ArkanoidBlock>>> _blocks;
	UINT _poolcountX = 20;
	UINT _poolcountY = 20;
};

