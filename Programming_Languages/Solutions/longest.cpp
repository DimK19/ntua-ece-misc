// SOURCE: https://www.geeksforgeeks.org/longest-subarray-having-average-greater-than-or-equal-to-x-set-2/
#include<cstdio>
#include<vector>
#include<stack>
#define MAX_M 500005

using namespace std;

int max_index_diff(vector<int>& arr, int m);

int main(int argc, char **argv)
{
	int n, m, t;
	vector<int> arr(MAX_M), prefix_sum(MAX_M);
	
	FILE* fp = fopen(argv[1], "rt");
    // FILE *fp = fopen("longest.in7", "rt");
	if(fp == NULL) return 1; // File not found
	
	fscanf(fp, "%d%d", &m, &n);
	for(int i = 0; i < m; ++i)
	{
		fscanf(fp, "%d", &t);
		arr[i] = - t - n;
	}
	
	prefix_sum[0] = arr[0];
	for(int i = 1; i < m; ++i) prefix_sum[i] = prefix_sum[i - 1] + arr[i];
	
	int ans = max_index_diff(prefix_sum, m);
	printf("%d", ans);
	
	return 0;
}

int max_index_diff(vector<int>& arr, int m)
{
	int max_diff;
    int i, j;
 
    int LMin[m], RMax[m];
 
    LMin[0] = arr[0];
    for (i = 1; i < m; ++i) LMin[i] = min(arr[i], LMin[i - 1]);
 
    RMax[m - 1] = arr[m - 1];
    for (j = m - 2; j >= 0; --j) RMax[j] = max(arr[j], RMax[j + 1]);
 
    i = 0, j = 0, max_diff = -1;
    while (j < m && i < m)
    {
        if (LMin[i] < RMax[j])
		{
			max_diff = max(max_diff, j - i);
            j++;
        }
        else i++;
    }
 
	if(i == 0) max_diff++;
    return max_diff;
}

