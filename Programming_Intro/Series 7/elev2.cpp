#include<iostream>
#include<climits>

using namespace std;

int main()
{
	int n, b, x, counter = 0;
	cin>>n>>b;
	
	int w[b+1];
	for(int i = 0; i <= b; ++i) w[i] = 0;
	int left = INT_MAX, right = INT_MIN;
	
	for(int i = 0; i < n; ++i)
	{
		cin>>x;
		++w[x];
		left = left < x ? left : x;
		right = right > x ? right : x;
	}
	
	while(left <= right)
	{
		if(left + right <= b)
		{
			--w[left];
			while(!w[left]) ++left;
		}
		// always guaranteed to take in at least the person with weight right, because they're the heaviest
		++counter;
		--w[right];
		while(!w[right]) --right;
	}
	
	cout<<counter<<'\n';
	
	return 0;
}
