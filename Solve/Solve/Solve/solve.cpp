#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<utility>
#include<vector>

using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;

	if (a > b)
		cout << ">" << endl;
	else if (a < b)
		cout << "<" << endl;
	else 
		cout << "==" << endl;
}