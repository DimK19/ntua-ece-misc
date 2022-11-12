#ifndef CONTEST
#include <iostream>

using namespace std;

struct list_node
{
	int data;
	list_node *next;
};

struct tree_node
{
	int data;
	tree_node *left, *right;
};

#endif

// YOUR SOLUTION GOES HERE -- YOU DON'T NEED TO ERASE THE REST
// -----------------------------------------------------------
// MAKE SURE THAT YOUR SUBMISSION COMPILES, OTHERWISE YOU WILL
// GET ZERO POINTS TODAY AND THAT WILL BE A PITY!
// ------------------------(snip)-----------------------------

#include<queue>

int sum(list_node *n)
{
	int sum = 0;
	while(n != nullptr)
	{
		sum += n->data;
		n = n->next;
	}

	return sum;
}

bool is_arithmetic_progression(list_node *n)
{
	if(n == nullptr || n->next == nullptr) return true;
	
	int diff = n->next->data - n->data;
	n = n->next;
	while(n->next != nullptr)
	{
		if(n->next->data - n->data != diff) return false;
		n = n->next;
	}
	
	return true;
}

int count_smaller_than(tree_node *t, int x)
{
	if(t == nullptr) return 0;
	int counter = 0;
	queue<tree_node *> q;
	q.push(t);
	while(!q.empty())
	{
		if(q.front()->data > x) ++counter;
		if(q.front()->left != nullptr) q.push(q.front()->left);
		if(q.front()->right != nullptr) q.push(q.front()->right);
		q.pop();
	}

	return counter;
}

bool find(tree_node *t, int x)
{
	if(t == nullptr) return false;
	queue<tree_node *> q;
	q.push(t);
	while(!q.empty())
	{
		if(q.front()->data == x) return true;
		if(q.front()->left != nullptr) q.push(q.front()->left);
		if(q.front()->right != nullptr) q.push(q.front()->right);
		q.pop();
	}

	return false;
}

bool is_bst(tree_node *t)
{
	if(t == nullptr) return true;
	if(t->left != nullptr && t->data < t->left->data) return false;
	if(t->right != nullptr && t->data > t->right->data) return false;
	return is_bst(t->left) && is_bst(t->right);
}

// ------------------------(snip)-----------------------------
// YOUR SOLUTION ENDS HERE -- YOU DON'T NEED TO ERASE THE REST

#ifndef CONTEST

list_node * list(int x, list_node *next)
{
	list_node *n = new list_node;
	n->data = x;
	n->next = next;
	return n;
}

tree_node * tree(int x, tree_node *left, tree_node *right)
{
	tree_node *n = new tree_node;
	n->data = x;
	n->left = left;
	n->right = right;
	return n;
}

int main()
{
	list_node *l = list(42, list(17, list(69, list(37, nullptr))));
	cout << "l = 42 -> 17 -> 69 -> 37" << endl;
	cout << "sum(l) = " << sum(l) << endl;
	cout << "is_arithmetic_progression(l) = " << (is_arithmetic_progression(l) ? "true" : "false") << endl;

	tree_node *t = tree(42,
						tree(17,
							tree(22, nullptr, tree(6, nullptr, nullptr)),
								tree(4, nullptr, tree(78, nullptr, nullptr))),
						tree(37,
								nullptr,
								tree(89, nullptr, nullptr)));
	cout << "t =    42" << endl;
	cout << "      /  \\" << endl;
	cout << "    17    37" << endl;
	cout << "   /  \\    \\" << endl;
	cout << " 22    4    89" << endl;
	cout << "   \\    \\" << endl;
	cout << "    6    78" << endl;
	cout << "count_smaller_than(t, 50) = " << count_smaller_than(t, 50) << endl;
	cout << "find(t, 17) = " << (find(t, 17) ? "true" : "false") << endl;
	cout << "is_bst(t) = " << (is_bst(t) ? "true" : "false") << endl;
}

#endif

