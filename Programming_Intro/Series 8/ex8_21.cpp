#include<iostream>

using namespace std;

struct node
{
	int value;
	node *left, *right;
};

class queue
{
	public:
		queue();
		void push(node *x);
		int size();
		node* Front();
		void pop();
	
	private:
		struct qnode
		{
			node *data;
			qnode *next;
		};
		qnode *front, *rear;
};

class stack
{
	public:
		stack();
		bool empty();
		void push(node *x);
		node* top();
		void pop();
		
	private:
		struct snode
		{
			node *data;
			snode *next;
		};
		snode *head;
};

class bstree
{
	public:
		bstree();
		int height();
		void insert(int x);
		int search(int x); // root is at level 1, return 0 if x is not found
		int min();
		int max();
		void inorder(); // In-order traversal
		void preorder(); // Pre-order traversal
		void postorder(); // Post-order traversal
	
	private:
		node *root;
};

queue::queue()
{
	front = rear = nullptr;
}

void queue::push(node *x)
{
	qnode *p = new qnode;
	p->data = x;
	p->next = nullptr;

	if(front == nullptr) front = p;
	else rear->next = p;

	rear = p;
}

int queue::size()
{
	if(front == nullptr) return 0;
	
	qnode *p = front;
	int s = 0;
	while(p != nullptr)
	{
		p = p->next;
		++s;
	}
	
	return s;
}

node* queue::Front()
{
	return front->data;
}

void queue::pop()
{
	if(front == rear) rear = nullptr;

	qnode *p = front;
	front = front->next;
	delete p;
}

stack::stack()
{
	head = nullptr;
}

bool stack::empty()
{
	return head == nullptr;
}

void stack::push(node *x)
{
	snode *p = new snode;
	p->data = x;
	p->next = head;
	head = p;
}

void stack::pop()
{
	snode *p = head;
	head = head->next;
	delete p;
}

node* stack::top()
{
	return head->data;
}

bstree::bstree()
{
	root = nullptr;
}

int bstree::height()
{
	if(root == nullptr) return 0;
	
	queue q;
	q.push(root);
	
	int height = 0;
	
	while(true)
	{
		int nodes = q.size();
		if(!nodes) return height;
		
		++height;
		
		while(nodes > 0)
		{
			node *first = q.Front();
			q.pop();
			
			if(first->left != nullptr) q.push(first->left);
			if(first->right != nullptr) q.push(first->right);
			
			--nodes;
		}
	}
}

void bstree::insert(int x)
{
	node *p = new node;
	p->value = x;
	p->left = nullptr;
	p->right = nullptr;
	
	node *q = root;
	node *r = nullptr;
	while(q != nullptr)
	{
		r = q;
		if(p->value < q->value) q = q->left;
		else q = q->right;
	}
	
	if(r == nullptr) root = p;
	else if(p->value < r->value) r->left = p;
	else r->right = p;
}

int bstree::search(int x)
{
	node *p = root;
	int level = 1;
	while(p != nullptr && x != p->value)
	{
		if(x < p->value) p = p->left;
		else p = p->right;
		++level;
	}
	
	if(p == nullptr) return 0;
	
	return level;
}

int bstree::min()
{
	node *p = root;
	int min;
	while(p != nullptr)
	{
		min = p->value;
		p = p->left;
	}
	
	return min;
}

int bstree::max()
{
	node *p = root;
	int max;
	while(p != nullptr)
	{
		max = p->value;
		p = p->right;
	}
	
	return max;
}

void bstree::inorder()
{
	stack s;
	node *current = root;
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
				cout<<current->value<<' ';
				current = current->right;
			}
			else break;
		}
	}
}

void bstree::preorder()
{
	if(root == nullptr) return;

	stack s;
	s.push(root);

	while(!s.empty())
	{
		node *n = s.top();
		cout<<n->value<<' ';
		s.pop();
	
		if (n->right) s.push(n->right);
		if (n->left) s.push(n->left);
	}
}

void bstree::postorder()
{
	if(root == nullptr) return;

	stack s1, s2;

	s1.push(root);
	node *n;

	while(!s1.empty())
	{
		n = s1.top();
		s1.pop();
		s2.push(n);

		if(n->left != nullptr) s1.push(n->left);
		if(n->right != nullptr) s1.push(n->right);
	}

	while (!s2.empty())
	{
		n = s2.top();
		s2.pop();
		cout<<n->value<<' ';
	}
}

int main()
{
	int n, m, x;
	bstree bst;
	
	cin>>n;
	for(int i = 0; i < n; ++i)
	{
		cin>>x;
		bst.insert(x);
	}
	
	cin>>m;
	int a[m];
	for(int i = 0; i < m; ++i)
	{
		cin>>x;
		a[i] = bst.search(x);
	}
	
	cout<<bst.height()<<'\n';
	
	cout<<bst.min()<<' '<<bst.max()<<'\n';
	
	for(int i = 0; i < m - 1; ++i) cout<<a[i]<<' ';
	cout<<a[m-1]<<'\n';
	
	bst.inorder();
	cout<<"end\n";
	bst.preorder();
	cout<<"end\n";
	bst.postorder();
	cout<<"end\n";
	
	return 0;
}
