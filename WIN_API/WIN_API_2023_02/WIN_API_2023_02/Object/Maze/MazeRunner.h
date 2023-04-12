#pragma once
class MazeRunner
{
public :
	MazeRunner(shared_ptr<Maze> maze);
	~MazeRunner();

	void Update();

	void LeftHand();
	bool CanGo(int y, int x);

private :
	shared_ptr<Maze> _maze;

	Vector2 _pos;
	Dir _direction = Dir::DIR_UP;

	vector<Vector2> _path;
	int _pathindex = 0;
	float _time = 0.0f;
};

