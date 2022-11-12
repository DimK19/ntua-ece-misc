#include<iostream>
#define SIZE 150
#define MAX_NUMS 22499  // 150^2-1

typedef int square[SIZE][SIZE];

int sumln(square B, int line, int N)
{
    int sum = B[line][0];

    for(int i=1; i<N; ++i)
        sum += B[line][i];
          
    return sum;
}

int sumcol(square B, int column, int N)
{
    int sum = B[0][column];

    for(int i=1; i<N; ++i)
        sum += B[i][column];
          
    return sum;
}

int diag_sum(square B, int N)
{
    int sum = 0;
      
    for(int i=0; i<N; ++i)
        sum += B[i][i];
          
    return sum;
}

int inv_diag_sum(square B, int N)
{
    int sum = 0;
      
    for(int i=0; i<N; ++i)
        sum += B[i][N-i-1];
          
    return sum;
}

int main()
{
    square B;
    int N, sums[2*SIZE];
    bool found[MAX_NUMS] = {0};
    bool flag = true;
            
    std::cin>>N;
              
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            std::cin>>B[i][j];
            found[B[i][j]] = true;
        }
                
    int size = N*N - 1;
    for(int i=0; i<size; ++i)
        if(!found[i])
        {
            flag = false;
            break;
        }
                    
    if(flag)
    {
        sums[0] = sumln(B, 0, N);
        for(int i=1; i<N; ++i)
        {
            sums[i] = sumln(B, i, N);
            if(sums[i]!=sums[0])
            {
                flag = false;
                break;
            }
        }
    }
                      
    if(flag)
    { 
        sums[N] = sumcol(B, 0, N);
        for(int i=1; i<N; ++i)
        {
            sums[i+N] = sumcol(B, i, N);
            if(sums[i]!=sums[N])
            {
                flag = false;
                break;
            }
        }
    }
                        
    if(flag && (diag_sum(B, N)!=sums[0] || inv_diag_sum(B, N)!=sums[0]))
        flag = false;
                          
    if(flag)
        std::cout<<"yes\n";
    else
        std::cout<<"no\n";
                              
    return 0;
}