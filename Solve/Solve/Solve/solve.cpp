#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<utility>
#include<vector>
#include<cmath>

using namespace std;

int main()
{
	int a = 0;

	cin >> a;

	if (a <= 100 && a >= 90)
		cout << "A" << endl;
	else if (a <= 89 && a >= 80)
		cout << "B" << endl;
	else if (a <= 79 && a >= 70)
		cout << "C" << endl;
	else if (a <= 69 && a >= 60)
		cout << "D" << endl;
	else
		cout << "F" << endl;

}