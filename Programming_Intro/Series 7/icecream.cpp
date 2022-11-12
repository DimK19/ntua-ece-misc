#include<iostream>

using namespace std;

int main()
{
  int n, k;
  
  cin>>n>>k;
        
  long long a[n];
  for(int i = 0; i < n; ++i) cin>>a[i];
            
  int l, r, counter, max;
  l = 0;
  r = counter = max = 1;
              
  while(r < n && l <= r)
  {
    if(a[r] - a[l] <= 2 * k)
    {
      ++r;
      ++counter;
    }
    else
    {
      ++l;
      --counter;
    }

    if(counter > max) max = counter;
  }
  
  cout<<max<<'\n';

  return 0;
}
