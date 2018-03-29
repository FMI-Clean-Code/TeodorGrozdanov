#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

//Asserts there are predefined operators < and > for the type T

template<class T>
class BOT
{
	struct Node
	{
		T value;
		Node* left, *right;
		int rightSubT;				//# of nodes in right subT. Added for counting inversions
		Node(const T&, Node* l = nullptr, Node* r = nullptr);
	};

	Node* copy(Node* crr);
	void del(Node* crr);
	void add(T el, Node*& crr);		//Adds equal to the right for the purpose of counting inversions correctly

	Node* root;
	int inversions;					//Added for counting inversions
public:
	

	BOT(std::vector<T> v = {});
	BOT(const BOT<T>& other);
	const BOT<T>& operator =(const BOT<T>& other);
	~BOT();

	void add(T);
	int getInversions();
	bool areSorted();

	template<class TT>
	friend std::ostream& operator<< (std::ostream& os, const BOT<TT>& bot);
};

template<class T>
BOT<T>::BOT(std::vector<T> v = {}) : root(nullptr), inversions(0)
{
	int size = v.size();
	for (int i = 0; i < size; i++)
		add(v[i]);
}

template<class T>
typename BOT<T>::Node* BOT<T>::copy(Node* crr)
{
	if (crr)
		return new Node(crr->value, copy(crr->left), copy(crr->right));
	return nullptr;
}

template<class T>
BOT<T>::Node::Node(const T& el, Node* l = nullptr, Node* r = nullptr) : value(el), left(l), right(r), rightSubT(0) {}

template<class T>
BOT<T>::BOT(const BOT<T>& other)
{
	root = copy(other.root);
}

template<class T>
const BOT<T>& BOT<T>::operator =(const BOT<T>& other)
{
	if (this != &other)
	{
		del(root);
		root = copy(other.root);
	}
	return *this;
}

template<class T>
void BOT<T>::del(Node* crr)
{
	if (crr)
	{
		del(crr->left);
		del(crr->right);
		delete crr;
	}
}

template<class T> 
BOT<T>::~BOT()
{
	del(root);
}

template<class T>
void BOT<T>::add(T el, Node*& crr)
{
	if (crr)
	{
		if (el < crr->value)
		{
			inversions += crr->rightSubT + 1;	//inversions rise by the number of nodes in the right subtree of the node + the node itsef
			add(el, crr->left);
		}
		else
		{
			(crr->rightSubT)++;
			add(el, crr->right);
		}
	}
	else
		crr = new Node(el);
}

template<class T>
void BOT<T>::add(T el)
{
	add(el, root);
}

template<class T>
int BOT<T>::getInversions()
{
	return inversions;
}

template<class T>
bool BOT<T>::areSorted()
{
	return getInversions() == 0;
}

template<class T>
std::ostream& operator <<(std::ostream& os, const BOT<T>& bot)
{
	typename BOT<T>::Node* crr, *noSuccessor;
	noSuccessor = (typename BOT<T>::Node*)INT_MIN;
	std::queue<typename BOT<T>::Node*> q;
	if(bot.root)
		q.push(bot.root);
	q.push(nullptr);
	while (q.size() > 1)
	{
		crr = q.front();
		q.pop();
		if (crr != nullptr)
		{
			if (crr != noSuccessor)
			{
				os << crr->value << ' ';
				if (crr->left)
					q.push(crr->left);
				else q.push(noSuccessor);
				if (crr->right)
					q.push(crr->right);
				else q.push(noSuccessor);
			}
			else os << "N ";
		}
		else
		{
			q.push(nullptr);
			os << '\n';
		}
	}
	return os;
}