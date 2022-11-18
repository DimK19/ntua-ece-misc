/* 
any MST is also MBST
find MST with Prim
answer is heaviest edge
*/
#include<cstdio>
#include<list>
#include<set>
#include<queue>
#include<algorithm>
#include<climits>
#include<tuple>
#include<fstream>
#define MAXN 1005

using namespace std;

typedef pair<int, int> pi;
typedef tuple<int, int, int> triplet;

class Graph
{
	private:
		int vertices;
		pi *parent;
		vector<pi> *adj, *mst_adj;
		bool *seen, *visited;
	
	public:
		Graph(int V);
		~Graph();
	
		void add_edge(int src, int dest, int weight);
		void find_mst(int src);
		void print_mst();
		int get_mbp_length(int src, int dest);
};

Graph::Graph(int V)
{
	this->vertices = V;
	adj = new vector<pi>[V];
	mst_adj = new vector<pi>[V];
	parent = new pi[V];
	seen = new bool[V];
	visited = new bool[V];
}

Graph::~Graph()
{
	delete[] adj;
	delete[] mst_adj;
	delete[] seen;
	delete[] visited;
}

void Graph::add_edge(int u, int v, int weight)
{
	adj[u].push_back(make_pair(weight, v));
	adj[v].push_back(make_pair(weight, u));

	return ;
}

// a crude approximation of Prim
void Graph::find_mst(int src = 0)
{
	// at each step
	// min weight edge of search front
	// if dest vertex of edge not in tree
	// put edge in tree
	
	/*
	// debugging
	for(int i = 0; i < vertices; ++i)
		for(auto p : adj[i])
			printf("src %d weight %d dest %d\n", i, p.first, p.second);
	*/
	
	seen[src] = true;
	// std::greater<T> to reverse the sorting order (descending by default)
	priority_queue<triplet, vector<triplet>, greater<triplet> > search_front;
	// each triplet is an edge: weight, dest, src
	for(auto p : adj[src]) search_front.push(make_tuple(p.first, p.second, src));
	int counter = 1;
	while(counter < vertices)
	{
		int edge_weight = get<0>(search_front.top());
		int edge_dest = get<1>(search_front.top());
		int edge_src = get<2>(search_front.top());
		search_front.pop();
		// printf("%d\n", edge_src);
		// printf("%d %d\n", edge_weight, edge_dest);
		if(!seen[edge_dest])
		{
			mst_adj[edge_src].push_back(make_pair(edge_weight, edge_dest));
			mst_adj[edge_dest].push_back(make_pair(edge_weight, edge_src));
			for(auto p : adj[edge_dest]) search_front.push(make_tuple(p.first, p.second, edge_dest));
			seen[edge_dest] = true;
			counter++;
		}
	}
}

// debugging
void Graph::print_mst()
{
	for(int i = 0; i < this->vertices; ++i)
		for(auto p : mst_adj[i]) printf("vertex %d vertex %d edge with weight %d\n", i + 1, p.second + 1, p.first);
}

// BFS
int Graph::get_mbp_length(int src, int dest)
{
	fill_n(visited, vertices, false);
	queue<triplet> Q;
	for(auto p : mst_adj[src]) Q.push(make_tuple(p.first, p.second, src));
	
	parent[src] = make_pair(0, -1);
	
	while(!Q.empty())
	{
		int edge_weight = get<0>(Q.front());
		int edge_dest = get<1>(Q.front());
		int edge_src = get<2>(Q.front());
		// printf("%d -> %d\n", edge_src + 1, edge_dest + 1);
		Q.pop();
		parent[edge_dest] = make_pair(edge_weight, edge_src);
		visited[edge_src] = true;
		if(edge_dest == dest)
		{
			// printf("found\n");
			vector<int> ans;
			ans.push_back(edge_weight);
			int i = dest;
			while(parent[i].second != -1)
			{
				ans.push_back(parent[i].first);
				i = parent[i].second;
			}
			
			return *max_element(ans.begin(), ans.end());
		}
		
		for(auto p : mst_adj[edge_dest])
			if(!visited[p.second]) Q.push(make_tuple(p.first, p.second, edge_dest));
	}
	
	return -1;
}

int main()
{
	//ifstream in("in32.txt");
	int N, M, Q;
	scanf("%d%d", &N, &M);
	//in >> N >> M;
	
	Graph g(N);
	
	int x, y, d;
	while(M--)
	{
		scanf("%d%d%d", &x, &y, &d);
		//in >> x >> y >> d;
		g.add_edge(x - 1, y - 1, d);
	}
	
	g.find_mst();
	
	scanf("%d", &Q);
	//in >> Q;
	while(Q--)
	{
		scanf("%d%d", &x, &y);
		//in >> x >> y;
		printf("%d\n", g.get_mbp_length(x - 1, y - 1));
	}
	
	// g.print_mst();
	
	return 0;
}
