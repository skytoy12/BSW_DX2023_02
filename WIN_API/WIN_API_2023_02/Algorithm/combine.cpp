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
int chache[100];

int facto(int n)
{
	if (n <= 0)
		return 1;
	if (chache[n] != -1)
		return chache[n];
	chache[n] = n * facto(n - 1);
	return chache[n];
}

int combination(int a, int b)
{
	return facto(a) / (facto(a - b) * facto(b));
}

int main()
{
	for (int i = 0; i < 100; i++)
	{
		chache[i] = -1;
	}
	int a = facto(5);
	cout << a << endl;
	int b = combination(10, 5);
	cout << b << endl;
	return 0;
}