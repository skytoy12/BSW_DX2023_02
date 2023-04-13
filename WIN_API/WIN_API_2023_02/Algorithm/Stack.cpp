#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;
// 1. 발자취 남기게 하기(발자취 색은 아무거나)
// 2. stack(후입선출), queue(선입선출)에 대해 조사해오기
//    팬케이크         줄서기
// 3. extra stack... stack자료구조 구현해오기

template <typename T>
class MyStack
{
public :
	void push(const T& value)
	{
		v.push_back(value);
	}

	void pop()
	{
		v.pop_back();
	}

	const T& top()
	{
		return v.back();
	}

	bool empty()
	{
		return v.size() == 0;
	}

private :
	vector<T> v;
};

int Stack() 
{
	stack<int> s;

	s.push(5);
	s.push(8);
	s.push(3);
	s.push(1);
	s.push(9);

	while (true)
	{
		if (s.empty() == true)
			break;

		int value = s.top();
		cout << value << endl;
		s.pop();
	}


	return 0;
}