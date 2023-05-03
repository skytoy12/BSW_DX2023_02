#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <windows.h>

// nCr = (n-1)Cr + (n-1)C(r-1)

using namespace std;
vector<vector<int>> chache;




int combination(int n, int r)
{
	if (n < 0 || n < r || r < 0)
		return 0;
	if (n == r)
		return 1;
	if (chache[n][r] != -1)
		return chache[n][r];
	return chache[n][r] = combination(n - 1, r) + combination(n - 1, r - 1);
}

int main()
{
	chache = vector<vector<int>>(101, vector<int>(101, -1));
	
	int b = combination(100, 5);
	cout << b << endl;
	return 0;
}