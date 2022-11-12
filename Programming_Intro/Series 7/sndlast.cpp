#include<iostream>

int main()
{
	int N, last_dig;
	
	std::cin>>N;
	
	N /= 10;
	
	last_dig = N % 10;
	
	std::cout<<last_dig<<'\n';
	
	return 0;
}
