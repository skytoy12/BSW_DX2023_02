#include "framework.h"
#include "MazeRunner.h"

MazeRunner::MazeRunner(shared_ptr<Maze> maze)
 : _maze(maze)
	,_pos(maze->Start())
{
	// LeftHand();
	// DFS
	_visited = vector<vector<bool>>(maze->GetY(), vector<bool>(maze->GetX(), false));
	
	// DFS(_pos);

	// BFS
	// BFS(_pos);
	
	// Djikstra
	
	// Dijkstra();

	// Astar
	Astar();
}

MazeRunner::~MazeRunner()
{
	_maze = nullptr;
}

void MazeRunner::Update()
{
	if (_pathindex >= _path.size())
	{
		_maze->CreateMazeByKruskal();
		_pathindex = 0;
		_path.clear();
		Astar();
		return;
	}

	_time += 0.5f;
	
	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathindex];
		
		if (_pathindex > 0)
		{
			_maze->GetBlock(_path[_pathindex-1].y, _path[_pathindex - 1].x)->SetType(MazeBlock::BlockType::FOOT_PRINT);
		}

		_pathindex++;
	}

	_maze->GetBlock((int)_pos.y, (int)_pos.x)->SetType(MazeBlock::BlockType::PLAYER);
}

void MazeRunner::LeftHand()
{
	Vector2 pos = _pos; // 첫 시작 위치
	Vector2 endPos = _maze->End();
	_direction = Dir::DIR_UP;
	_path.push_back(pos);

	Vector2 frontPos[4] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // DOWN
		Vector2(-1,0) // LEFT
	};

	while (pos != endPos)
	{
		// 현재 바라보는 방향 기준으로 왼쪽
		int newDir = (_direction - 1 + Dir_COUNT) % Dir_COUNT;
		Vector2 oldDirVector2 = frontPos[_direction]; // 기존 방향
		Vector2 newDirVector2 = frontPos[newDir];     // 왼손 짚는 방향

		// 왼손이 가리키는 방향으로 전진할 수 있는지 확인
		Vector2 newGo = pos + newDirVector2;
		Vector2 oldGo = pos + oldDirVector2;
		if (CanGo(newGo.y, newGo.x))
		{
			_direction = static_cast<Dir>(newDir);
			pos += newDirVector2;
			_maze->GetBlock(pos.y, pos.x)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}
		
		// 현재 바라보는 방향으로 전진할 수 있는지 확인
		else if (CanGo(oldGo.y, oldGo.x))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		// 왼쪽, 앞이 다 막혀있다면 시계방향으로 회전
		else
		{
			_direction = static_cast<Dir>((_direction + 1 + Dir_COUNT) % Dir_COUNT);
		}
	}

	stack<Vector2> s;
	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	s.push(_path.back());
	_path.clear();

	while (true)
	{
		if (s.empty() == true)
			break;
		_path.push_back(s.top());
		s.pop();
	}
	std::reverse(_path.begin(), _path.end());
}

void MazeRunner::DFS(Vector2 here)
{
	if(_visited[(int)here.y][(int)here.x] == true)
		return;

	Vector2 endPos = _maze->End();

	if (_visited[endPos.y][endPos.x] == true)
		return;

	_visited[(int)here.y][(int)here.x] = true;
	_maze->GetBlock(here.y, here.x)->SetType(MazeBlock::BlockType::VISITED);
	_path.push_back(here);

	Vector2 frontPos[4] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // DOWN
		Vector2(-1,0) // LEFT
	};

	for (int i = 0; i < 4; i++)
	{
		Vector2 there = here + frontPos[i];
		if (_visited[there.y][there.x] == true)
			continue;
		if (CanGo(there.y, there.x) == false)
			continue;

		DFS(there);
	}

}

void MazeRunner::BFS(Vector2 start)
{
	queue<Vector2> queue;
	queue.push(start);
	_visited[start.y][start.x] = true;
	_parent[start.y][start.x] = start;
	_maze->GetBlock(start.y, start.x)->SetType(MazeBlock::BlockType::VISITED);

	while (true)
	{
		Vector2 endPos = _maze->End();
		if (queue.empty() == true)
			break;
		Vector2 here = queue.front();
		queue.pop();
		if (_visited[endPos.y][endPos.x] == true)
			break;

		Vector2 frontPos[8] =
		{
			Vector2(0,-1), // UP
			Vector2(1,0), // RIGHT
			Vector2(0,1), // DOWN
			Vector2(-1,0), // LEFT
			Vector2(1,-1), // RIGHTUP
			Vector2(1,1), // RIGHTDOWN
			Vector2(-1,-1), // RIGHTDOWN
			Vector2(-1,1), // RIGHTDOWN
		};

		for (int i = 0; i < 4; i++)
		{
			Vector2 there = here + frontPos[i];
			if (_visited[there.y][there.x] == true)
				continue;
			if (CanGo(there.y, there.x) == false)
				continue;
			queue.push(there);
			_parent[there.y][there.x] = here;
			_visited[there.y][there.x] = true;
			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}

	Vector2 endPos = _maze->End();
	Vector2 targetPos = endPos;
	vector<Vector2> a;
	while (true)
	{
		if (_parent[targetPos.y][targetPos.x] == targetPos)
			break;
		targetPos = _parent[targetPos.y][targetPos.x];
		a.push_back(targetPos);
	}

	reverse(a.begin(), a.end());
	for (auto ready : a)
	{
		_path.push_back(ready);
	}
	_path.push_back(endPos);
}

void MazeRunner::Dijkstra()
{
	_best = vector<vector<int>>(_maze->GetY(), vector<int>(_maze->GetX(), INT_MAX));
	_DjParent = vector<vector<Vector2>>(_maze->GetY(), vector<Vector2>(_maze->GetX(), Vector2(-1, -1)));
	_DjVisited = vector<vector<bool>>(_maze->GetY(), vector<bool>(_maze->GetX(), false));
	Vector2 endPos = _maze->End();
	priority_queue<Vertex_Dijkstra, vector<Vertex_Dijkstra>, greater<Vertex_Dijkstra>> pq;
	Vertex_Dijkstra startV = Vertex_Dijkstra(_maze->Start(), 0);
	pq.push(startV);
	_best[startV.vertexPos.y][startV.vertexPos.x] = 0;
	_DjVisited[startV.vertexPos.y][startV.vertexPos.x] = true;
	_DjParent[startV.vertexPos.y][startV.vertexPos.x] = startV.vertexPos;

	while (true)
	{
		if (pq.empty())
			break;
		int cost = pq.top().g;
		Vector2 here = pq.top().vertexPos;
		pq.pop();

		if (here == endPos)
			break;

		Vector2 frontPos[8] =
		{
			Vector2(0,-1), // UP
			Vector2(1,0), // RIGHT
			Vector2(0,1), // DOWN
			Vector2(-1,0), // LEFT
			Vector2(1,-1), // RIGHTUP
			Vector2(1,1), // RIGHTDOWN
			Vector2(-1,-1), // RIGHTDOWN
			Vector2(-1,1), // RIGHTDOWN
		};

		int Dijkstra_Dis[8] =
		{
			10,
			10,
			10,
			10,
			14,
			14,
			14,
			14
		};
		
		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];
			if (here == there)
				continue;
			if (CanGo(there.y, there.x) == false)
				continue;

			
			float nextCost = _best[here.y][here.x] + Dijkstra_Dis[i];
			


			// 나중에 방문하려 했는데 이미 좋은 값이 있었다
			if (nextCost >= _best[there.y][there.x])
				continue;

		
			// 방문
			Vertex_Dijkstra v = Vertex_Dijkstra(there, nextCost);
			pq.push(v);
			_best[there.y][there.x] = nextCost;
			_DjVisited[there.y][there.x] = true;
			_DjParent[there.y][there.x] = here;
			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}

	Vector2 targetPos = endPos;
	while (true)
	{
		if (_DjParent[targetPos.y][targetPos.x] == targetPos)
			break;
		targetPos = _DjParent[targetPos.y][targetPos.x];
		_path.push_back(targetPos);
	}
	std::reverse(_path.begin(), _path.end());
	_path.push_back(endPos);
}

void MazeRunner::Astar()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // RIGHT
		Vector2(0,1), // DOWN
		Vector2(-1,0), // LEFT
		Vector2(1,-1), // RIGHTUP
		Vector2(1,1), // RIGHTDOWN
		Vector2(-1,-1), // RIGHTDOWN
		Vector2(-1,1), // RIGHTDOWN
	};

	int Astar_Dis[8] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	_parent = vector<vector<Vector2>>(_maze->GetY(), vector<Vector2>(_maze->GetX(), Vector2(-1, -1)));
	_best = vector<vector<int>>(_maze->GetY(), vector<int>(_maze->GetX(), INT_MAX));

	Vector2 start = _maze->Start();
	Vector2 end = _maze->End();

	Vertex v;
	v.vertexPos = start;
	v.g = 0;
	v.h = start.MahattanDistance(end);
	v.f = v.g + v.h;

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	pq.push(v);

	_best[v.vertexPos.y][v.vertexPos.x] = v.f;
	_parent[v.vertexPos.y][v.vertexPos.x] = v.vertexPos;

	while (true)
	{
		if (pq.empty() == true)
			break;
		int g = pq.top().g;
		int h = pq.top().h;
		int f = pq.top().f;

		int cost = f;

		Vector2 here = pq.top().vertexPos;
		pq.pop();
		
		if (here == end)
			break;
		
		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];
			if (there == here)
				continue;
			if (CanGo(there.y, there.x) == false)
				continue;

			int newG = g + Astar_Dis[i];
			int newH = there.MahattanDistance(end);
			int newCost = newG + newH;
			

			if (newCost > _best[there.y][there.x])
				continue;

		

			Vertex astarV;
			astarV.vertexPos = there;
			astarV.g = newG;
			astarV.h = newH * 10;
			astarV.f = newCost;

			pq.push(astarV);
			_best[there.y][there.x] = newCost;
			_parent[there.y][there.x] = here;
			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}

	}

	Vector2 targetPos = end;
	while (true)
	{
		if (_parent[targetPos.y][targetPos.x] == targetPos)
			break;
		targetPos = _parent[targetPos.y][targetPos.x];
		_path.push_back(targetPos);
	}
	std::reverse(_path.begin(), _path.end());
	_path.push_back(end);

}

bool MazeRunner::CanGo(int y, int x)
{
	if (_maze->GetBloockType(y, x) == MazeBlock::BlockType::DISABLE ||
		_maze->GetBloockType(y, x) == MazeBlock::BlockType::NONE)
	{
		return false;
	}
	return true;
}


