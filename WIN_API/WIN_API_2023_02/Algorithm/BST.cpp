#include "BST.h"
#include <iostream>

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node(key);
	if (_root == nullptr)
	{
		_root = newNode;
		return;
	}
	Node* node = _root;
	Node* parent = nullptr;

	while (true)
	{
		if (node == nullptr)
			break;

		parent = node;

		if (key < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	newNode->parent = parent;

	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

void BinarySearchTree::PrintTree(Node* root)
{
	// ���� ��ȸ : ��Ʈ - ���� - ������
	// ���� ��ȸ : ���� - ��Ʈ - ������
	// ���� ��ȸ : ���� - ������ - ��Ʈ

	if (root == nullptr)
		return;
	PrintTree(root->left);
	std::cout << root->key << std::endl;
	PrintTree(root->right);
}

Node* BinarySearchTree::Search(Node* root, int key)
{
	if (root == nullptr)
		return nullptr;

	Node* findNode = root;
	
	while (true)
	{
		if (findNode == nullptr)
			break;
		if (findNode->key == key)
			break;
		else if (findNode->key > key)
			findNode = findNode->left;
		else
			findNode = findNode->right;
	}
	if (findNode == nullptr)
	{
		std::cout << "ã�� ��尡 �������� �ʽ��ϴ�" << std::endl;
	}
	else
		std::cout << "ã�� ��尡 �����մϴ�" << std::endl;
	return findNode;

	/*if (root == nullptr)
		return root;

	if (root->key == key)
		return root;

	if (key < root->key)
		return Search(root->left, key);
	else
		return Search(root->right, key);*/
}

Node* BinarySearchTree::Min(Node* root)
{
	// �ݺ� ����
	/*if (root == nullptr)
		return nullptr;

	Node* minNode = root;
	while (true)
	{
		if (minNode->left != nullptr)
			minNode = minNode->left;
		else
			break;
	}
	return minNode;*/

	// ��� ����
	// 1. ��������

	if (root == nullptr)
		return nullptr;
	if (root->left != nullptr)
		return Min(root->left);
	return root;
}

Node* BinarySearchTree::Max(Node* root)
{
	/*if (root == nullptr)
		return nullptr;

	Node* maxNode = root;
	while (true)
	{
		if (maxNode->right != nullptr)
			maxNode = maxNode->right;
		else
			break;
	}
	return maxNode;*/

	// ��� ����
	// 1. ��������

	if (root == nullptr)
		return nullptr;
	if (root->right != nullptr)
		return Max(root->right);
	return root;
}

Node* BinarySearchTree::Previous(Node* root)
{
	if (root == nullptr)
		return nullptr;
	
	Node* preNode = root;
	if (preNode->left == nullptr)
		return nullptr;
	if (preNode->left != nullptr)
		preNode = preNode->left;
	while (true)
	{
		if (preNode->right == nullptr)
			break;
		else
			preNode = preNode->right;
	}

	return preNode;
}

Node* BinarySearchTree::Next(Node* root)
{
	if (root == nullptr)
		return nullptr;

	Node* nextNode = root;
	if (nextNode->right == nullptr)
		return nullptr;
	if (nextNode->right != nullptr)
		nextNode = nextNode->right;
	while (true)
	{
		if (nextNode->left == nullptr)
			break;
		else
			nextNode = nextNode->left;
	}

	return nextNode;
}

void BinarySearchTree::Replace(Node* node1, Node* node2)
{
	// node1�� ��Ʈ��忴��.
	if (node1->parent == nullptr)
		_root = node2;
	// node1�� �θ��ʿ��� ���ʿ� �ִ� ����� ��
	else if (node1 == node1->parent->left)
	{
		node1->parent->left = node2;
	}
	// node1�� �θ��ʿ��� �����ʿ� �ִ� ����� ��
	else
	{
		node1->parent->right = node2;
	}
	
	if (node2 != nullptr)
	{
		node2->parent = node1->parent;
	}

	delete node1;
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;
	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	else
	{
		Node* pre = Previous(node);
		node->key = pre->key;
		node->data = pre->data;
		Delete(pre);
	}
}
