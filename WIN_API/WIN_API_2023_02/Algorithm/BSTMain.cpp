#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>


using namespace std;

#include "BST.h"


int main()
{
	BinarySearchTree tree;

	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(8);
	tree.Insert(7);
	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(10);
	tree.Insert(9);
	tree.Insert(100);

	
	tree.PrintTree(tree._root);
	//tree.Search(tree._root, 10);
	//cout << tree.Max(tree._root)->key << endl;
	//cout << tree.Min(tree._root)->key << endl;
	//cout << tree.Previous(tree._root)->key << endl;
	//cout << tree.Next(tree._root)->key << endl;
	tree.Delete(tree.Search(tree._root, 8));
	cout << "8을 삭제한 후" << endl;
	tree.PrintTree(tree._root);

	return 0;
}