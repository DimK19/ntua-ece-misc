#include<iostream>
#include<cmath>

int num_of_digits(int x)
{
	int i = 1;
	while(x/10)
	{
		x /= 10;
    	++i;
	}

	return i;
}

bool equal(int x, int N)
{
	int digits[8];
	int size = num_of_digits(x);
	int temp = x;
	int div = pow(10, size-1);

	for(int i=0; i<size; ++i)
	{
    	digits[i] = temp / div;
    	temp %= div;
    	div /= 10;
	}

	int sum=0;
	for(int i=0; i<size; ++i) sum += pow(digits[i], N);

	if(sum == x) return true;
	return false;
}

int main()
{
	int N;
	std::cin>>N;

	for(int i=0; i<100000000; ++i)
    	if(equal(i, N)) std::cout<<i<<'\n';
    
	return 0;
}

