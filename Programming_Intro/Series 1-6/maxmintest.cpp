#include<cstdio>

typedef int list[100][100];

int min2d(list B, int i, int M)
{
  int m = B[i][0];
  for(int j=1; j<M; ++j)
    if(B[i][j]<m) m = B[i][j];

  return m;
}

int max2d(list B, int i, int N)
{
  int m = B[0][i];

  for(int j=1; j<N; ++j)
    if(B[j][i]>m) m = B[j][i];

  return m;
}


int min1d(int A[], int size)
{
  int m = A[0];

  for(int i=1; i<size; ++i)
    if(A[i]<m) m = A[i];

  return m;
}

int max1d(int A[], int size)
{
  int m = A[0];

  for(int i=0; i<size; ++i)
    if(A[i]>m) m =A[i];

  return m;
}

int main()
{
	int N, M;
  	list B;
  	int mins[100], maxs[100];

  	scanf("%i%i", &N, &M);
	
  	for(int i=0; i<N; ++i)
    	for(int j=0; j<M; ++j)
    	  scanf("%i", &B[i][j]);

  	for(int i=0; i<M; ++i)
    	maxs[i] = max2d(B, i, N);

  	for(int i=0; i<N; ++i)
    	mins[i] = min2d(B, i, M);

  	int minmax = min1d(maxs, M);
  	int maxmin = max1d(mins, N);

  	printf("%i\n%i", minmax, maxmin);
  	
  	return 0;
}
