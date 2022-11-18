#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<algorithm>
#define MAX_N 100005

using namespace std;

int perm[MAX_N], uf[MAX_N];

// linear quick find from Sedgewick
void unify(int x, int y, int N)
{
	int t = uf[x];
	for(int i = 1; i <= N; ++i)
		if(uf[i] == t) uf[i] = uf[y];
}

bool validate(int N)
{
	for(int i = 1; i <= N; ++i)
		if(uf[i] != uf[perm[i]]) return false;
	return true;
}

/* Compile and test with
 * g++ -std=c++11 a.exe teleports.cpp
 * a.exe .\\teleports\\input0.txt
 * more .\\teleports\\output0.txt
 */
int main(int argc, char *argv[])
{
	ifstream in(argv[1]);
	int N, M, x, y, d;
	typedef tuple<int, int, int> triplet;
	in >> N >> M;
	for(int i = 1; i <= N; ++i)
	{
		in >> perm[i];
		uf[i] = i;
	}
	
	vector<triplet> portals; // edges
	for(int i = 0; i < M; ++i)
	{
		in >> x >> y >> d;
		portals.push_back(make_tuple(x, y, d));
	}
	
	sort(portals.begin(), portals.end(), [](triplet tr1, triplet tr2){return get<2>(tr1) > get<2>(tr2);});
	
	// for(auto it : portals) cout << get<2>(it) << '\n';
	
	int ans = -1;
	vector<triplet>::iterator it = portals.begin();
	while(it != portals.end())
	{
		unify(get<0>(*it), get<1>(*it), N);
		if(validate(N))
		{
			ans = get<2>(*it);
			break;
		}
		++it;
	}

	cout << ans << '\n';
	
	return 0;
}
