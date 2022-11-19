#include<cstdio>
#include<vector>
#include<stack>
#define MAX_N 1001
#define MAX_M 1001

using namespace std;

int main(int argc, char **argv)
{
	vector< vector< pair<int, int> > > adj(MAX_N * MAX_M); // adjacency list
	bool escapeable[MAX_N][MAX_M], visited[MAX_N][MAX_M];
	vector< pair<int, int> > exits;
	
	int n, m;
	char direction;
	
	FILE* fp = fopen(argv[1], "rt");
    // FILE *fp = fopen("fairmaze.in3", "rt");
	if(fp == NULL) return 1; // File not found
	
	fscanf(fp, "%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		fscanf(fp, "%c", &direction); // consume newline
        // create inverse of graph
		for(int j = 0; j < m; ++j)
		{
			escapeable[i][j] = false;
			visited[i][j] = false;
			fscanf(fp, "%c", &direction);
			if(direction == 'U')
			{
				if(i - 1 >= 0) adj[(i - 1) * m + j].push_back(make_pair(i, j));
				else
				{
					exits.push_back(make_pair(i, j));
					escapeable[i][j] = true;
				}
			}
			else if(direction == 'D')
			{
				if(i + 1 < n) adj[(i + 1) * m + j].push_back(make_pair(i, j));
				else
				{
					exits.push_back(make_pair(i, j));
					escapeable[i][j] = true;
				}
			}
			else if(direction == 'L')
			{
				if(j - 1 >= 0) adj[i * m + j - 1].push_back(make_pair(i, j));
				else
				{
					exits.push_back(make_pair(i, j));
					escapeable[i][j] = true;
				}
			}
			else if(direction == 'R')
			{
				if(j + 1 < m) adj[i * m + j + 1].push_back(make_pair(i, j));
				else
				{
					exits.push_back(make_pair(i, j));
					escapeable[i][j] = true;
				}
			}
		}
	}
	
	stack< pair<int, int> > S;
	
	for(vector< pair<int, int> >::iterator ex = exits.begin(); ex != exits.end(); ++ex) S.push(*ex);
	// for each known exit, run dfs on its adjacency list
	while(!S.empty())
	{
		int i = S.top().first * m + S.top().second;
		S.pop();
		int s = adj[i].size();
		for(int j = 0; j < s; ++j)
		{
			if(!visited[adj[i][j].first][adj[i][j].second]) S.push(make_pair(adj[i][j].first, adj[i][j].second));
			visited[adj[i][j].first][adj[i][j].second] = true;
			escapeable[adj[i][j].first][adj[i][j].second] = true;
		}
	}
	
	int counter = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) if(!escapeable[i][j]) counter++;
	
	printf("%d", counter);
	
	return 0;
}
