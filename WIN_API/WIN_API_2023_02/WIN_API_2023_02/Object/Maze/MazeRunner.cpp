#include "framework.h"
#include "MazeRunner.h"

MazeRunner::MazeRunner(shared_ptr<Maze> maze)
 : _maze(maze)
	,_pos(maze->Start())
{
	LeftHand();
}

MazeRunner::~MazeRunner()
{
	_maze = nullptr;
}

void MazeRunner::Update()
{
	if (_pathindex >= _path.size())
		return;

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
	Vector2 pos = _pos; // ù ���� ��ġ
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
		// ���� �ٶ󺸴� ���� �������� ����
		int newDir = (_direction - 1 + Dir_COUNT) % Dir_COUNT;
		Vector2 oldDirVector2 = frontPos[_direction]; // ���� ����
		Vector2 newDirVector2 = frontPos[newDir];     // �޼� ¤�� ����

		// �޼��� ����Ű�� �������� ������ �� �ִ��� Ȯ��
		Vector2 newGo = pos + newDirVector2;
		Vector2 oldGo = pos + oldDirVector2;
		if (CanGo(newGo.y, newGo.x))
		{
			_direction = static_cast<Dir>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}
		
		// ���� �ٶ󺸴� �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(oldGo.y, oldGo.x))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		// ����, ���� �� �����ִٸ� �ð�������� ȸ��
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

bool MazeRunner::CanGo(int y, int x)
{
	if (_maze->GetBloockType(y, x) == MazeBlock::BlockType::DISABLE ||
		_maze->GetBloockType(y, x) == MazeBlock::BlockType::NONE)
	{
		return false;
	}
	return true;
}

