#pragma once
class ArkanoidBlocks
{
public:
	ArkanoidBlocks();
	~ArkanoidBlocks();

	void Update();
	void Render(HDC hdc);
	vector<vector<shared_ptr<ArkanoidBlock>>> GetBlocks() { return _arkanoidBlocks; }
	

private:
	vector<vector<shared_ptr<ArkanoidBlock>>> _arkanoidBlocks;
	UINT _poolCountX = 10;
	UINT _poolCountY = 6;
};

