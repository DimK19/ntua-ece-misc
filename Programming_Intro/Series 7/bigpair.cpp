#include<cstdio>
#define MAX 1000000

using namespace std;

int a[MAX], b[MAX];

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);

  for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for(int j = 0; j < m; ++j) scanf("%d", &b[j]);

  long long pairs = 0; // pair counter
  int j = 0;

  for(int i = 0; i < n; ++i)
  {
    while(j < m && a[i] > b[j]) ++j;
    pairs += j;
  }

  printf("%lld\n", pairs);

  return 0;
}
