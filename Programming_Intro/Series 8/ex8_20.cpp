// AC IN ONE GO
#include<iostream>

using namespace std;

class list
{
	public:
		list();
		bool empty();
		int size();
		void add(int k, int x);
		int get(int k);
		void remove(int k);
		int searchMF(int x);
	
	private:
		struct node
		{
			int value;
			node *next;
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
	node *it = head;
	while(it != nullptr)
	{
		it = it->next;
		++s;
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
	else if(k == 1)
	{
		p->next = head;
		head = p;
	}
	else
	{
		node *it = head;
		--k;
		while(--k) it = it->next;
		p->next = it->next;
		it->next = p;
	}
}

int list::get(int k)
{
	node *it = head;
	while(k--) it = it->next;
	
	return it->value;
}

void list::remove(int k)
{
	node *it = head;
	if(k == 1)
	{
		head = head->next;
		delete it;
	}
	else
	{
		--k;
		while(--k) it = it->next;
		node *q = it->next;
		it->next = q->next;
		delete q;
	}
}

int list::searchMF(int x)
{
	node *p = head;
	int pos = 1;
	while(p != nullptr && p->value != x)
	{
		p = p->next;
		++pos;
	}
	
	if(!p) return 0; // not found
	
	add(1, x);
	remove(pos+1);
	
	return pos;
}

int main()
{
	int n, m, k, x, sum;
	list l;
	
	sum = 0;
	
	cin>>n;
	for(int i = 0; i < n; ++i)
	{
		cin>>k>>x;
		l.add(k, x);
	}
	
	cin>>m;
	for(int i = 0; i < m; ++i)
	{
		cin>>x;
		sum += l.searchMF(x);
	}
	
	cout<<sum<<'\n';
	
	return 0;
}
