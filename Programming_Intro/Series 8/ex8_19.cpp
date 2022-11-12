// AC IN ONE GO
#include<iostream>

using namespace std;

class list
{
	public:
		list();
		bool empty();
		int size();
		void add(int k, int x); // insert x at position k
		int get(int k); // get value at position k
		void remove(int k); // delete value at position k
		
	private:
		struct node
		{
			int value;
			node* next;
		};
		node *head;
};

list::list()
{
	head = nullptr;
}

bool list::empty()
{
	return head == nullptr;
}

int list::size()
{
	int s = 0;
	node *p = head;
	
	while(p != nullptr)
	{
		++s;
		p = p->next;
	}
	
	return s;
}

void list::add(int k, int x)
{
	node *p = new node;
	p->value = x;

	if(head == nullptr)
	{
		p->next = nullptr;
		head = p;
	}
	else if(k == 1)	// insert at front
	{
		p->next = head;
		head = p;
	}
	else
	{
		node *it = head;
		--k; // decrement k so that after the loop, it points
		while(--k) it = it->next; // at the node, after which the new one must be placed
		p->next = it->next;
		it->next = p;
	}
}

int list::get(int k)
{
	if(head != nullptr)
	{
		node *p = head;
		while(k--) p = p->next;
		return p->value;
	}
}

void list::remove(int k)
{
	node *p = head;
	
	if(k == 1)
	{
		head = head->next;
		delete p;
	}
	else // delete node after p
	{
		--k;
		while(--k) p = p->next;
		node *q = p->next;
		p->next = q->next;
		delete q;
	}
}

int main()
{
	int n, m, k, x;
	list l;
	
	cin>>n;
	for(int i = 0; i < n; ++i)
	{
		cin>>k>>x;
		l.add(k, x);
	}
	
	cin>>m;
	for(int i = 0; i < m; ++i)
	{
		cin>>k;
		l.remove(k);
	}
	
	cin>>k;
	cout<<l.size()<<' '<<l.get(k-1)<<'\n'; 	// get(0) is the first node
	
	return 0;
}
