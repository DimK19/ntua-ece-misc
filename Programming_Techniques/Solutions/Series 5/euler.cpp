#include<iostream>
#include<queue>

using namespace std;

void adj_list(int *adj, int M)
{
	int a, b;
	
	for(int i = 0; i < M; ++i)
	{
		cin>>a>>b;
		++adj[a];
		++adj[b];
	}
	
	return ;
}

int main()
{
	int N, M;
	cin>>N>>M;
	
	int *adj = new int[N];
	for(int i = 0; i < N; ++i) adj[i] = 0;
	adj_list(adj, M);
	
	queue<int> q;
	for(int i = 0; i < N; ++i) if(adj[i] % 2) q.push(i);
	
	if(q.empty()) cout<<"CYCLE\n";
	else if(q.size() == 2)
	{
		cout<<"PATH "<<q.front()<<' ';
		q.pop();
		cout<<q.front()<<'\n';
	}
	else cout<<"IMPOSSIBLE\n";
	
	return 0;
}
