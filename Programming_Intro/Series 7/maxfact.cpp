// Find the largest natural number whose factorial doesn't exceed n
// n < 2 bil
#include<cstdio>
#define ll long long

using namespace std;

int main()
{
	ll facts[13]; // 12! is the largest factorial < 2 bil
	facts[0] = 1;
	for(int i = 1; i < 13; ++i) facts[i] = facts[i-1] * i;
	
	ll n;
	scanf("%lld", &n);
	
	int m = 0;
	while(facts[m] <= n) ++m;
	
	--m;
	printf("%d\n", m);
	
	return 0;
}
