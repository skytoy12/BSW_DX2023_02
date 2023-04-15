#pragma once
class ArkanoidBlock
{
public:

	enum class ArkanoidBlockType
	{
		NONE,
		NOMALBLOCK,
		HARDBLOCK,
		ITEMBLOCK

	};

	ArkanoidBlock();
	~ArkanoidBlock();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _rect->SetCenter(pos); }

	void SetType(ArkanoidBlockType type) { _type = type; }
	ArkanoidBlockType GetType() { return _type; }
	bool IsAlive() { return _isAlive; }
	void SetAlive(bool alive) { _isAlive = alive; }
	shared_ptr<Collider> GetEachBlock() { return _rect; }
	


private:
	vector<HBRUSH> _brushes;
	bool _isAlive = true;
	
	shared_ptr<Collider> _rect;
	ArkanoidBlockType _type = ArkanoidBlockType::NONE;
};

