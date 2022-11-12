#include<iostream>

using namespace std;  

struct node  
{
    int value;
    node *left, *right;
};

class bstree
{
	public:
		bstree();
		int height(node *x);
		void insert(int x);
		int search(int x);
		int min();
		int max();
		void inorder(node *x);
		void preorder(node *x);
		void postorder(node *x);
		node *root;
};

bstree::bstree()
{
    root = nullptr;
}

int bstree::height(node *x)
{
    if(x == nullptr) return 0;
	
	int r = height(x->right);
	int l = height(x->left);
	
	return r > l ? ++r : ++l;
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

void bstree::inorder(node *x)
{
	if(x == nullptr) return;
	inorder(x->left);
	cout<<x->value<<' ';
	inorder(x->right);
}

void bstree::preorder(node *x)
{
	if(x == nullptr) return;
	cout<<x->value<<' ';
	preorder(x->left);
	preorder(x->right);
}

void bstree::postorder(node *x)
{
	if(x == nullptr) return;
	postorder(x->left);
	postorder(x->right);
	cout<<x->value<<' ';
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
    
	cout<<bst.height(bst.root)<<'\n';
    
	cout<<bst.min()<<' '<<bst.max()<<'\n';
    
	for(int i = 0; i < m - 1; ++i) cout<<a[i]<<' ';
	cout<<a[m-1]<<'\n';
    
	bst.inorder(bst.root);
	cout<<"end\n";
	bst.preorder(bst.root);
	cout<<"end\n";
	bst.postorder(bst.root);
	cout<<"end\n";
	
	return 0;
}  