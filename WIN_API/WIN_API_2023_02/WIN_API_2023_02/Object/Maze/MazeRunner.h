#pragma once
class MazeRunner
{
public :
	MazeRunner(shared_ptr<Maze> maze);
	~MazeRunner();

	void Update();

	void LeftHand();

	void DFS(Vector2 start);

	void BFS(Vector2 start);

	void Djikstra(Vector2 start);

	bool CanGo(int y, int x);

private :
	shared_ptr<Maze> _maze;

	Vector2 _pos;
	Dir _direction = Dir::DIR_UP;

	vector<Vector2> _path;
	int _pathindex = 0;
	float _time = 0.0f;

	// DFS
	vector<vector<bool>> _visited;
	// BFS
	vector<vector<Vector2>> _parent;

	// Djikstra
	struct Vertex
	{
		Vertex(Vector2 pos, int g) : vertexPos(pos), g(g) {}
		bool operator<(const Vertex& other) const
		{
			return g < other.g;
		}

		bool operator>(const Vertex& other) const
		{
			return g > other.g;
		}

		Vector2 vertexPos;
		int g;

	};
	vector<int> best;
	vector<vector<Vector2>> DjParent;
};

