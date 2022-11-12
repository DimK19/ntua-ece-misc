#include<iostream>
#include<stack>
#include<queue>
#include<algorithm>
#include<string>

using namespace std;

class lexicon
{
	public:
		lexicon();
		~lexicon();

		void insert(const string &s, int count = 1);
		int lookup(const string &s) const;
		int depth(const string &s);
		void replace(const string &s1, const string &s2);
								
	private:
		struct node
		{
			string str;
			int counter = 0;
			node *left, *right;
			friend class lexicon;
		};
		node *root;
	
	friend ostream& operator<<(ostream &out, const lexicon &l);
};

lexicon::lexicon()
{
	root = nullptr;
}

lexicon::~lexicon()
{
	queue<node *> q;
	q.push(root);
	while(!q.empty())
	{  
		if((q.front())->left != nullptr) q.push((q.front())->left);
		if((q.front())->right != nullptr) q.push((q.front())->right);
		node *temp = q.front();
		q.pop();
		delete temp;
	}
}

void lexicon::insert(const string &s, int count)
{
	node *q = root;
	node *r = nullptr;
	while(q != nullptr)
	{
		r = q;
		if(r->str == s) break;
		else if(s < q->str) q = q->left;
		else q = q->right;
	}
			
	if(r != nullptr && r->str == s) r->counter += count;
	else
	{
		node *p = new node;
		p->str = s;
		p->left = nullptr;
		p->right = nullptr;
		if(r == nullptr)
		{
			root = p;
			root->counter = count;
		}
		else if(p->str < r->str)
		{
			r->left = p;
			r->left->counter = count;
		}
		else if(p->str > r->str)
		{
			r->right = p;
			r->right->counter = count;
		}
	}
}

int lexicon::lookup(const string &s) const
{
	node *p = root;
	while(p != nullptr && s != p->str)
	{
		if(s < p->str) p = p->left;
		else p = p->right;
	}
		
	if(p == nullptr) return 0;

	return p->counter;
}

int lexicon::depth(const string &s)
{
	node *p = root;
	int depth = 1;
	while(p != nullptr && s != p->str)
	{
		if(s < p->str) p = p->left;
		else p = p->right;
		depth++;
	}
		  
	if(p == nullptr) return 0;

	return depth;
}

void lexicon::replace(const string &s1, const string &s2)
{
	if(!lookup(s1)) return;
  
	node *first, *second;
	first = root;
	second = first;
	while(first != nullptr && s1 != first->str)
	{
		second = first;
		if(s1 < first->str) first = first->left;
		else first = first->right;
	}
			
	int save = first->counter;
	if(first->left == nullptr)
	{
		if(first == root)
		{
			root = first->right;
			first = nullptr;
		}
		else		
		  if(second->left == first) second->left = first->right;
		  else second->right = first->right;

		delete first;
	}
	else if(first->right == nullptr)
	{
		if(first == root)
		{
			root = first->left;
			first = nullptr;
		}
		else
		  if(second->left == first) second->left = first->left;
		  else second->right = first->left;

		delete first;
	}
	else
	{
		node *temp = first->left;
		node *before_temp = first;
		while(temp->right != nullptr)
		{
			before_temp = temp;
			temp = temp->right;
		}
		
		if(temp != nullptr)
		{
			swap(temp->str, first->str);
			swap(temp->counter, first->counter);
		}

		if(before_temp->left == temp) before_temp->left = nullptr;
		else before_temp->right = nullptr;
		delete temp;
	}
				  
	if(!lookup(s2)) insert(s2, save);
	else
	{
		node *p = root;
		while(p != nullptr && s2 != p->str)
		{
			if(s2 < p->str) p = p->left;
			else p = p->right;
		}
		p->counter += save;
	}
}

ostream& operator<<(ostream &out, const lexicon &l)
{
	stack<lexicon::node *> s;
	lexicon::node *current = l.root;
	while(true)
	{
		if(current != nullptr)
		{
			s.push(current);
			current = current->left;
		}
		else
		{
			if(!s.empty())
			{
				current = s.top();
				s.pop();
				out<<current->str<<' '<<current->counter<<'\n';
				current = current->right;
			}
			else break;
		}
	}
		  
	return out;
}

#ifndef CONTEST

int main()
{
	lexicon l;
	
	l.insert("a");
	l.insert("aa");
	l.insert("aaa");
	l.insert("aaaa");
	l.insert("aaaaa");
	l.insert("aaaaaa");
	l.insert("aaaaaaa");
	l.insert("b");
	l.insert("bb");
	l.insert("bbb");
	l.insert("bbbb");
	l.insert("bbbbb");
	l.insert("bbbbbb");
	l.insert("bbbbbbb");
	l.insert("c");
	l.insert("cc");
	l.insert("ccc");
	l.insert("cccc");
	l.insert("ccccc");
	l.insert("cccccc");
	l.insert("ccccccc");
	l.insert("d");
	l.insert("dd");
	l.insert("ddd");
	l.insert("dddd");
	l.insert("ddddd");
	l.insert("dddddd");
	l.insert("ddddddd");

	cout<<l<<'\n';
	
	l.replace("a", "foo");
	l.replace("aa", "foo");
	l.replace("aaa", "foo");
	l.replace("aaaa", "foo");
	l.replace("aaaaa", "foo");
	l.replace("aaaaaa", "foo");
	l.replace("aaaaaaa", "foo");
	l.replace("b", "foo");
	l.replace("bb", "foo");
	l.replace("bbb", "foo");
	l.replace("bbbb", "foo");
	l.replace("bbbbb", "foo");
	l.replace("bbbbbb", "foo");
	l.replace("bbbbbbb", "foo");
	l.replace("c", "foo");
	l.replace("cc", "foo");
	l.replace("ccc", "foo");
	l.replace("cccc", "foo");
	l.replace("ccccc", "foo");
	l.replace("cccccc", "foo");
	l.replace("ccccccc", "foo");
	l.replace("d", "foo");
	l.replace("dd", "foo");
	l.replace("ddd", "foo");
	l.replace("dddd", "foo");
	l.replace("ddddd", "foo");
	l.replace("dddddd", "foo");
	l.replace("ddddddd", "foo");

	cout<<l<<'\n';

	return 0;
}

#endif
