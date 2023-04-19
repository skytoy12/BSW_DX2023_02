#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>


using namespace std;

template <typename T>
class Priority_Queue
{
public :
	// 부모가 인덱스 n일 때
	// 자식은 n * 2 + 1, n * 2 + 2다
	void push(const T& value)
	{
		container.push_back(value);
		for (int i = 0; i < container.size(); i++)
		{
			if ((i * 2) + 1 >= container.size())
				return;
			if ((i * 2) + 2 >= container.size())
			{
				if (container[i] < container[(i * 2) + 1])
				{
					swap(container[i], container[(i * 2) + 1]);
				}
				return;
			}
			if (container[i] < container[(i * 2) + 1] || container[i] < container[(i * 2) + 2])
			{
				if (container[(i * 2) + 1] >= container[(i * 2) + 2])
					swap(container[i], container[(i * 2) + 1]);
				else
					swap(container[i], container[(i * 2) + 2]);
			}
		}
	}

	void pop()
	{
		if (container.empty() == true)
			return;
		swap(container[0], container.back());
		container.resize(container.size() - 1);
		for (int i = 0; i < container.size(); i++)
		{
			if ((i * 2) + 1 >= container.size())
				return;
			if ((i * 2) + 2 >= container.size())
			{
				if (container[i] < container[(i * 2) + 1])
				{
					swap(container[i], container[(i * 2) + 1]);
				}
				return;
			}
			if (container[i] < container[(i * 2) + 1] || container[i] < container[(i * 2) + 2])
			{
				if (container[(i * 2) + 1] >= container[(i * 2) + 2])
					swap(container[i], container[(i * 2) + 1]);
				else
					swap(container[i], container[(i * 2) + 2]);
			}
		}
	}

	const T& top() { return container[0]; }

	unsigned int size() { return container.size(); }

	bool empty() { return container.size() == 0; }

private :
	vector<T> container;
};

int main()
{
	// priority_queue는 완전이진트리로 구성되어있다
	// 완전이진트리는 배열을 이용해서 구현할 수 있다
	
	// 힙이론
	// 

	Priority_Queue<int> pq;
	pq.push(10);
	pq.push(7);
	pq.push(20);
	pq.push(4);
	pq.push(11);

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();
	return 0;
}