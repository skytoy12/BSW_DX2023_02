#pragma once
class MazeRunner
{
public :

	struct Vertex_Dijkstra
	{
		Vertex_Dijkstra(Vector2 pos, int g) : vertexPos(pos), g(g) {}
		bool operator<(const Vertex_Dijkstra& other) const
		{
			return this->g < other.g;
		}

		bool operator>(const Vertex_Dijkstra& other) const
		{
			return this->g > other.g;
		}

		Vector2 vertexPos;
		int g;
	};

	struct Vertex
	{
		Vector2 vertexPos;
		int g;
		int h;
		int f;

		bool operator<(const Vertex& other) const
		{
			return this->f < other.f;
		}

		bool operator>(const Vertex& other) const
		{
			return this->f > other.f;
		}
	};

	MazeRunner(shared_ptr<Maze> maze);
	~MazeRunner();

	void Update();

	void LeftHand();

	void DFS(Vector2 start);

	void BFS(Vector2 start);

	void Dijkstra();
	
	void Astar();

	bool CanGo(int y, int x);

private :
	shared_ptr<Maze> _maze;

	Vector2 _pos;
	Dir _direction = Dir::DIR_UP;

	vector<Vector2> _path;
	int _pathIndex = 0;
	float _time = 0.0f;

	// DFS
	vector<vector<bool>> _visited;
	// BFS
	vector<vector<Vector2>> _parent;

	// Djikstra
	
	vector<vector<int>> _best;
	vector<vector<Vector2>> _DjParent;
	vector<vector<bool>> _DjVisited;
};

