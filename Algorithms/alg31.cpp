/* 
graph vertices the members of the ring min(di)
edge weights the cost to go from one to another (also members of di)
min cost tree with Dijkstra (SPT shortest path tree)
answer each query in O(1)
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
#define ll long long int

using namespace std;

int d[MAXN];

typedef pair<int, int> pi;
typedef tuple<int, int, int> triplet;

class Graph
{
	private:
		int vertices;
		ll *sp;
		char *color;
		list<pi> *adj;
		set<int> *seen;
	
	public:
		Graph(int V);
		~Graph();
	
		void add_edge(int src, int dest, int weight);
		void shortest_paths(int src);
		void print_shortest_paths();
		ll get_sp_length(int dest);
};

Graph::Graph(int V)
{
	this->vertices = V;
	adj = new list<pi >[V];
	seen = new set<int>[V];
	color = new char[V];
	sp = new ll[V];
	fill_n(sp, V, INT_MAX); 
}

Graph::~Graph()
{
	delete[] adj;
	delete[] seen;
	delete[] color;
	delete[] sp;
}

void Graph::add_edge(int src, int dest, int weight)
{
	if(seen[src].find(dest) == seen[src].end())
	{
		adj[src].push_back(make_pair(weight, dest));
		seen[src].insert(dest);
	}
	else
		for(list<pi>::iterator it = adj[src].begin(); it != adj[src].end(); ++it)
			if(it->second == dest && it->first > weight)
			{
				it->first = weight;
				break;
			}

	return ;
}

// a crude approximation of Dijkstra
void Graph::shortest_paths(int src = 0)
{
	// at each step
	// min weight edge of search front
	// if weight < current weight for that edge
	// update its current weight and parent
	
	/*
	// debugging
	for(int i = 0; i < vertices; ++i)
		for(auto p : adj[i])
			printf("src %d weight %d dest %d\n", i, p.first, p.second);
	*/
	sp[src] = 0;
	// std::greater<T> to reverse the sorting order (descending by default)
	priority_queue<triplet, vector<triplet>, greater<triplet> > search_front;
	// each triplet is an edge: weight, dest, src
	for(auto p : adj[src]) search_front.push(make_tuple(p.first, p.second, src));
	while(!search_front.empty())
	{
		int edge_weight = get<0>(search_front.top());
		int edge_dest = get<1>(search_front.top());
		int edge_src = get<2>(search_front.top());
		search_front.pop();

		if(sp[edge_dest] > (sp[edge_src] + edge_weight))
		{
			sp[edge_dest] = sp[edge_src] + edge_weight;
			for(auto p : adj[edge_dest]) search_front.push(make_tuple(p.first, p.second, edge_dest));
		}
	}
}

// debugging
void Graph::print_shortest_paths()
{
	for(int i = 0; i < this->vertices; ++i) printf("%d %d\n", i, sp[i]);
}

ll Graph::get_sp_length(int dest)
{
	return sp[dest];
}

int main()
{
	//ifstream in("in31.txt");
    int N, Q, s;
    scanf("%d%d", &N, &Q);
	//in >> N >> Q;
    for(int i = 0; i < N; ++i) scanf("%d", &d[i]);//in >> d[i];
   
	int mindy = *min_element(d, d + N);
    Graph g(mindy);
	
	int w;
	for(int i = 0; i < mindy; ++i)
		for(int j = 0; j < N; ++j)
		{
			w = (i + d[j]) % mindy;
			if(w) g.add_edge(i, w, d[j]);
		}
	
	g.shortest_paths();
	// g.print_shortest_paths();
	
    while(Q--)
    {
        scanf("%d", &s);
		//in >> s;
		if(s >= g.get_sp_length(s % mindy)) printf("YES\n");
		else printf("NO\n");
    }

	return 0;
}
