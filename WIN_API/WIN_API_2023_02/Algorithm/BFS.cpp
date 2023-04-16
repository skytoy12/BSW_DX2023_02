#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

vector<vector<bool>> adjacent2;
vector<bool> visited;
vector<int> waiting;

void CreateGraphByMatrix()
{
	adjacent2 = vector<vector<bool>>(7, vector<bool>(7, false));
	visited = vector<bool>(7, false);

	adjacent2[0][0] = true;
	adjacent2[0][1] = true;
	adjacent2[0][2] = true;
	adjacent2[0][4] = true;

	adjacent2[1][0] = true;
	adjacent2[1][1] = true;

	adjacent2[2][0] = true;
	adjacent2[2][2] = true;
	adjacent2[2][3] = true;
	adjacent2[2][5] = true;

	adjacent2[3][2] = true;
	adjacent2[3][3] = true;

	adjacent2[4][0] = true;
	adjacent2[4][4] = true;
	adjacent2[4][6] = true;

	adjacent2[5][2] = true;
	adjacent2[5][5] = true;

	adjacent2[6][4] = true;
	adjacent2[6][6] = true;
}

void BFS(int start)
{
	
	while(true)
	{
		for (int there = 0; there < adjacent2.size(); there++)
		{
			// �������ֳ�?
			if (adjacent2[start][there] == true)
			{
				waiting.push_back(there);
				visited[there] = true;
			}
		}

		for (int there = 0; there < adjacent2.size(); there++)
		{
			if (adjacent2[start][there] == true && start < there)
				BFS(there);
		}
		
		int count = 0;

		for (auto visit : visited)
		{
			count = std::count(visited.begin(), visited.end(), true);
		}
		
		if (count == visited.size())
			break;
	}

	
	for (int i = 0; i < adjacent2.size(); i++)
	{
		cout << waiting[0] << "�� �湮�Ͽ����ϴ�" << endl;
		int deleteNum = waiting[0];
		waiting.erase(remove(waiting.begin(), waiting.end(), deleteNum));

	}

}



int main()
{
	CreateGraphByMatrix();
	BFS(0);
	return 0;
}