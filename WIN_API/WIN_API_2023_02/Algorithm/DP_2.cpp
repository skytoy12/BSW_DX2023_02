#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <windows.h>

using namespace std;

// LIS(Longest Increasing Sequence)
// 부분 증가 수열에서 제일 긴 수열 길이를 찾는다
// Seq : 1, 2, 9, 5, 8, 10

// 부분 수열 : 순서는 유지하되 인접하지 않을 수 도 있다
// 1, 2, 5 (O)
// 1, 2, 9, 8 (O)
// 2, 9, 1 (X)

// 부분 증가 수열 : 부분 수열이면서 점점 증가되는 순서로 유지되는 수열
// 1, 2, 5 (O)
// 1, 2, 9, 8 (X)

// vector<int> seq = {0, 5, 1, 2, 3, 1 };
vector<int> seq = {3, 5, 1, 2, 4, 1};

// LIS(0) = 0부터 시작해서 나올 수 있는 부분 증가 수열의 수
// LIS(5) : 1                         1
// LIS(4) : LIS(5) or LIS(5) + 1      1
// LIS(3) : LIS(4) or LIS(4) + 1      2
// LIS(2) : LIS(3) or LIS(3) + 1      
// LIS(1) : LIS(2) or LIS(2) + 1
// LIS(0) : LIS(1) or LIS(1) + 1
vector<int> cache = vector<int>(101, - 1);

int LIS(int pos)
{
	if (pos == seq.size() - 1)
	{
		cache[pos] = 1;
		return 1;
	}
	else if (seq[pos] < seq[pos + 1])
	{
		cache[pos] = LIS(pos + 1) + 1;
	}
	else
		cache[pos] = LIS(pos + 1);
	
	return cache[pos];
}

int main()
{
	cout << LIS(1) << endl;
	return 0;
}