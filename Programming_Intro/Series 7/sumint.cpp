#include<iostream>

typedef long long ll;

using namespace std;

int main()
{
	int N, x;
	ll K;
	cin>>N>>K;
	
	ll prefix_sum[N+1];
	prefix_sum[0] = 0;
	
	for(int i = 1; i <= N; ++i)
	{
		cin>>x;
		prefix_sum[i] = prefix_sum[i-1] + x;
	}
	
	ll counter = 0;
	int left, right;
	
	for(left = 1, right = 1; left <= N; ++left)
	{
		while(right <= N && prefix_sum[right] - prefix_sum[left-1] <= K) ++right;
		counter += right - left; // increasing the counter one by one makes it slower
	}
	
	cout<<counter<<'\n';
	
	return 0;
}
