#pragma once
#include<iostream>
using namespace std;

template<class TKey, class TVal>
struct BTreeNode
{
	TKey key;//ключ (не повторяються)
	TVal value;// значение
	BTreeNode* left = nullptr;// меньше 1 элемента
	BTreeNode* right = nullptr;// больше 1 элемента
	BTreeNode(TKey key, TVal val) : key(key), value(val) {}

	void print() const
	{
		if (left != nullptr) left->print();
		cout << value << "\n";
		if (right != nullptr) right->print();
	}

	void printDiapason(const TKey& key1, const TKey& key2) const
	{
		if (left != nullptr) left->printDiapason(key1, key2);
		if (this->key >= key2 && this->key <= key1)//если kay больше 2 и меньше 1 то показываем если нет идем на право и затем на лево и так до нахождения
			cout << this->value;
		if (right != nullptr) right->printDiapason(key1, key2);
	}

	void del()
	{
		if (left != nullptr) left->del();
		if (right != nullptr) right->del();
		delete this;
	}

	TVal* getValue(const TKey& key)
	{
		if (key == this->key) return &value;
		if (key < this->key && left != nullptr) return left->getValue(key);
		if (key > this->key && right != nullptr) return right->getValue(key);
		return nullptr;
	}
};

template<class TKey, class TVal>
class BTree
{
	static BTreeNode<TKey, TVal>* root;
public:
	~BTree();
	void clear();
	void print() const;
	bool isEmpty() const;
	TVal* getValue(const TKey& key);
	bool push(const TKey& key, const TVal& value);
	BTreeNode<TKey, TVal>* push_r(TKey key, TVal val, BTreeNode<TKey, TVal>*& node = root);
	void printDiapason(const TKey& key1, const TKey& key2);
	//BTreeNode<TKey, TVal>* find(const TKey& key);
};

template<class TKey, class TVal>
BTree<TKey, TVal>::~BTree() { this->clear(); }

template<class TKey, class TVal>
void BTree<TKey, TVal>::clear()
{
	if (root)
		root->del();
	root = nullptr;
}

template<class TKey, class TVal>
void BTree<TKey, TVal>::print() const
{
	if (root)
		root->print();
}

template<class TKey, class TVal>
bool BTree<TKey, TVal>::isEmpty() const { return root == nullptr; }

template<class TKey, class TVal>
TVal* BTree<TKey, TVal>::getValue(const TKey& key)
{
	if (root)
		return root->getValue(key);
	return nullptr;
}

template<class TKey, class TVal>
bool BTree<TKey, TVal>::push(const TKey& key, const TVal& value)
{
	if (!root)
	{
		root = new BTreeNode<TKey, TVal>(key, value);
		return true;
	}
	BTreeNode<TKey, TVal>* current = root;
	do
	{
		if (key < current->key)
		{
			if (current->left != nullptr)
				current = current->left;
			else
			{
				current->left = new BTreeNode<TKey, TVal>(key, value);
				return true;
			}
		}
		else if (key > current->key)
		{
			if (current->right != nullptr)
				current = current->right;
			else
			{
				current->right = new BTreeNode<TKey, TVal>(key, value);
				return true;
			}
		}
		else
			return false;
	} while (true);
}

template<class TKey, class TVal>
BTreeNode<TKey, TVal>* BTree<TKey, TVal>::push_r(TKey key, TVal value, BTreeNode<TKey, TVal>*& node)
{
	if (!node)
	{
		node = new BTreeNode<TKey, TVal>(key, value);
		return node;
	}
	if (key < node->key) node->left = push_r(key, value, node->left);
	else if (key > node->key) node->right = push_r(key, value, node->right);
	return node;
}

template<class TKey, class TVal>
void BTree<TKey, TVal>::printDiapason(const TKey& key1, const TKey& key2)
{
	if (root)
		root->printDiapason(key1, key2);
}

//template<class TKey, class TVal>
//BTreeNode<TKey, TVal>* BTree<TKey, TVal>::find(const TKey& key) {
//	BTreeNode<TKey, TVal>* current = root;
//	while (current != nullptr) {
//		if (key == current->key) {
//			return current;
//		}
//		else if (key < current->key) {
//			current = current->left;
//		}
//		else {
//			current = current->right;
//		}
//	}
//	return nullptr;
//}

template<class TKey, class TVal>
BTreeNode<TKey, TVal>* BTree<TKey, TVal>::root = nullptr;
