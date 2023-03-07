#include<cstdio>
#include<list>
#include<set>
#include<queue>
#include<algorithm>
#include<climits>
#include<tuple>
#include<fstream>
#include<iostream>
#include<chrono>
#define MAXN 1005
#define MAXM 10005
#define ll long long int

using namespace std;

ll sp[MAXN][MAXM];

typedef pair<int, int> pi;
typedef tuple<int, int, int> triplet;

priority_queue<triplet, vector<triplet>, greater<triplet> > search_front;
queue<triplet> Q;
vector<triplet> all_edges;

class Graph
{
	private:
		int vertices;
		bool *color;
		list<pi> *adj;
		set<int> *seen;
	
	public:
		Graph(int V, int E);
		~Graph();
	
		void add_edge(int src, int dest, int weight);
		void BFS(int src);
		void Dijkstra(int src);
		int k_skip(int src, int target, int K);
		void print_shortest_paths(int nullable_edges);
};

Graph::Graph(int V, int E)
{
	this->vertices = V;
	adj = new list<pi>[V + 1];
	seen = new set<int>[V + 1];
	color = new bool[V + 1];
	fill_n(color, V + 1, false);
	for(int i = 1; i <= V; ++i) fill_n(sp[i], E, INT_MAX); 
}

Graph::~Graph()
{
	delete[] adj;
	delete[] color;
}

void Graph::add_edge(int src, int dest, int weight)
{
	adj[src].push_back(make_pair(weight, dest));

	return ;
}

void Graph::BFS(int src = 0)
{
	for(auto p : adj[src])
	{
		Q.push(make_tuple(p.first, p.second, src));
		all_edges.push_back(make_tuple(p.first, p.second, src));
	}
	color[src] = true;
	
	while(!Q.empty())
	{
		int edge_weight = get<0>(Q.front());
		int edge_dest = get<1>(Q.front());
		int edge_src = get<2>(Q.front());
		Q.pop();

		if(!color[edge_dest])
			for(auto p : adj[edge_dest])
			{
				all_edges.push_back(make_tuple(p.first, p.second, edge_dest));
				if(!color[p.second])
					Q.push(make_tuple(p.first, p.second, edge_dest));
			}
			
		color[edge_dest] = true;
	}
}

void Graph::Dijkstra(int src = 0)
{
	// each triplet is an edge: weight, dest, src
	fill_n(color, this->vertices + 1, false);
	
	for(auto p : adj[src]) search_front.push(make_tuple(p.first, p.second, src));
	
	while(!search_front.empty())
	{
		int edge_weight = get<0>(search_front.top());
		int edge_dest = get<1>(search_front.top());
		int edge_src = get<2>(search_front.top());
		search_front.pop();

		if(sp[edge_dest][0] > (sp[edge_src][0] + edge_weight))
		{
			sp[edge_dest][0] = sp[edge_src][0] + edge_weight;
			for(auto p : adj[edge_dest])
				if(!color[p.second])
					search_front.push(make_tuple(p.first, p.second, edge_dest));
		}
		color[edge_src] = true;
	}
}

int Graph::k_skip(int src, int target, int K)
{
	// k nullable edges
	for(int k = 1; k <= K; ++k)
	{
		for(auto e: all_edges)
		{
			int edge_weight = get<0>(e);
			int edge_dest = get<1>(e);
			int edge_src = get<2>(e);
			
			sp[edge_dest][k] = min(min(sp[edge_dest][k], sp[edge_src][k] + edge_weight), sp[edge_src][k-1]);
		}
	}
	
	return sp[target][K];
}

// debugging
void Graph::print_shortest_paths(int nullable_edges)
{
	for(int i = 0; i <= 13; ++i)
	{
		printf("***** K = %d *****\n", i);
		for(int j = 1; j <= this->vertices; ++j) printf("%d %d\n", j, sp[j][i]);
	}
}

int main(int argc, char **argv)
{
	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
	auto t1 = high_resolution_clock::now();

	ifstream in(argv[1]);
    int N, M, B, s, t, u, v, w;
	in >> N >> M >> s >> t >> B;
    //scanf("%d%d%d%d%d", &N, &M, &s, &t, &B);
	
	Graph g(N, M);
    for(int i = 0; i < M; ++i)
	{
		//scanf("%d%d%d", &u, &v, &w);
		in >> u >> v >> w;
		g.add_edge(u, v, w);
	}
	
	for(int i = 0; i <= M; ++i) sp[s][i] = 0;
	
	g.BFS(s);
	g.Dijkstra(s);
	
	g.k_skip(s, t, M);
	int low = 0, high = M, middle;
	while(low < high)
	{
		middle = (low + high) / 2;
		if(sp[t][middle] <= B) high = middle;
		else low = middle + 1;
	}
	
	printf("%d\n", high);
	
    auto t2 = high_resolution_clock::now();
	
    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;


    std::cout << ms_double.count() << "ms\n";

	return 0;
}
