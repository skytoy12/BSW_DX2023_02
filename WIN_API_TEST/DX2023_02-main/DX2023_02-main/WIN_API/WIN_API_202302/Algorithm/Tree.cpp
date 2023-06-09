#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// 트리
// 1. 계층적 구조를 나타내기에 가장 적합한 자료구조
// 2. 부모와 자식관계로 이루어져있다.
// 3. 맨 상위 부모, 즉 루트는 무조건 하나다.
// 4. 트리를 잘라도 트리다. (재귀적 속성을 갖고 있다.)

struct Node
{
	Node() {}
	Node(string data) : data(data) {}
	~Node() {}

	Node* parent = nullptr;
	vector<Node*> children;

	string data;
};

Node* CreateTree()
{
	Node* root = new Node("개발팀");
	{
		Node* node = new Node("프로그래밍팀");
		root->children.push_back(node);
		{
			Node* leaf1 = new Node("클라이언트");
			node->children.push_back(leaf1);

			Node* leaf2 = new Node("서버");
			node->children.push_back(leaf2);

			Node* leaf3 = new Node("엔진");
			node->children.push_back(leaf3);
		}
	}

	{
		Node* node = new Node("기획팀");
		root->children.push_back(node);
		{
			Node* leaf1 = new Node("레벨디자인");
			node->children.push_back(leaf1);

			Node* leaf2 = new Node("스토리");
			node->children.push_back(leaf2);

			Node* leaf3 = new Node("밸런스");
			node->children.push_back(leaf3);
		}
	}

	{
		Node* node = new Node("아트팀");
		root->children.push_back(node);
		{
			Node* leaf1 = new Node("배경");
			node->children.push_back(leaf1);

			Node* leaf2 = new Node("모델링");
			node->children.push_back(leaf2);

			Node* leaf3 = new Node("UI");
			node->children.push_back(leaf3);
		}
	}

	return root;
}

void PrintTree(Node* node)
{
	cout << node->data << endl;

	for(auto child : node->children)
		PrintTree(child);
}

int main()
{
	Node* root = CreateTree();
	PrintTree(root->children[0]);

	return 0;
}