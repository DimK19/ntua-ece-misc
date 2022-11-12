#include<iostream>
#include<list>
#include<vector>
#include<algorithm>

using namespace std;

class Graph
{
	private:
		int vertices, *parent;
		char *color;
		list<int> *adj;
		void DFS(vector<int> &path, bool &flag) const;
		void DFS_visit(int u, vector<int> &path, bool &flag) const;
	
	public:
		Graph(int V);
		~Graph();
	
		void addEdge(int src, int dest);
		bool cycle(vector<int> &path) const;
};

Graph::Graph(int V)
{
	this->vertices = V;
	adj = new list<int>[V];
	color = new char[V];
	parent = new int[V];
}

Graph::~Graph()
{
	delete[] adj;
	delete[] color;
	delete[] parent;
}

void Graph::addEdge(int src, int dest)
{
	adj[src].push_back(dest);
	return ;
}

bool Graph::cycle(vector<int> &path) const
{
	bool flag = false;
	DFS(path, flag);
	return flag;
}

void Graph::DFS(vector<int> &path, bool &flag) const
{
	for(int i = 0; i < this->vertices; ++i)
	{
		this->color[i] = 'w';
		this->parent[i] = -1;
	}
  
	for(int i = 0; i < this->vertices; ++i) if(this->color[i] == 'w') DFS_visit(i, path, flag);
  
	return ;
}

void Graph::DFS_visit(int u, vector<int> &path, bool &flag) const
{
	this->color[u] = 'g';
	list<int>::iterator v;
	for(v = this->adj[u].begin(); v != this->adj[u].end(); ++v)
	{
		if(flag) return ;
		if(this->color[*v] == 'w')
		{
			this->parent[*v] = u;
			DFS_visit(*v, path, flag);
		}
		else if(color[*v] == 'g') // cycle found
		{
			flag = true;
			int a = u;
			while(a != *v)
			{
				path.insert(path.begin(), a);
				a = this->parent[a];
			}
			path.insert(path.begin(), a);
		}
	}

	this->color[u] = 'b';
}

#ifndef CONTEST
#include<fstream>

ifstream in("input.txt");

int main()
{
	int V, E;
	in>>V>>E;
	Graph g(V);
  
	for(int i = 0; i < E; ++i)
	{
		int a, b;
		in>>a>>b;
		g.addEdge(a, b);
	}

	vector<int> path;
	bool c = g.cycle(path);
  
	if(c)
	{
		cout<<"CYCLE: ";
		for(int i = 0; i < path.size(); ++i) cout<<path[i]<<(i == path.size() - 1 ? '\n' : ' ');
	}
	else cout<<"NO CYCLE\n";

	return 0;
}

#endif

