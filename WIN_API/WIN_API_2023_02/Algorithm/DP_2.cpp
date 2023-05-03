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
// �κ� ���� �������� ���� �� ���� ���̸� ã�´�
// Seq : 1, 2, 9, 5, 8, 10

// �κ� ���� : ������ �����ϵ� �������� ���� �� �� �ִ�
// 1, 2, 5 (O)
// 1, 2, 9, 8 (O)
// 2, 9, 1 (X)

// �κ� ���� ���� : �κ� �����̸鼭 ���� �����Ǵ� ������ �����Ǵ� ����
// 1, 2, 5 (O)
// 1, 2, 9, 8 (X)

// vector<int> seq = {0, 5, 1, 2, 3, 1 };
vector<int> seq = {3, 5, 1, 2, 4, 1};

// LIS(0) = 0���� �����ؼ� ���� �� �ִ� �κ� ���� ������ ��
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