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

// ENCHANT

// 강화하는데
// +1
// +2
// +3

// N강을 하고 싶다... 이때 강화하는 대로 나오는 모든 경우의 수
// 1 1 1
// 1 2
// 2 1
// 3

// 1111
// 112
// 121
// 13
// 211
// 22
// 31

// 11111
// 1112
// 1121
// 1211
// 2111
// 221
// 212
// 122
// 311
// 131
// 113
// 32
// 23

vector<int> cache = vector<int>(101, -1);
int Num = 10;
int Enchant(int N)
{
	
	//if (n > Num)
	//	return 0;
	//if (n == Num)
	//	return 1;

	//// 캐쉬
	//int& ref = cache[n];
	//if (ref != -1)
	//	return ref;

	//// 구하기
	//ref = Enchant(n + 1) + Enchant(n + 2) + Enchant(n + 3);
	//return ref;
	if (N == 0 || N == 1)
		return 1;
	if (N == 2)
		return 2;

	if (cache[N] != -1)
		return cache[N];

	cache[N] = Enchant(N - 1) + Enchant(N - 2) + Enchant(N - 3);

	return cache[N];
}

int main()
{
	
	cout << Enchant(0) << endl;
	return 0;
}