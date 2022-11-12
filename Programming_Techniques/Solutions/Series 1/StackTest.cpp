#include<iostream>
#include"Stackdemo.hpp"

int main()
{
	Stack<int> S(5);
	
	S.push(1);
	S.push(2);
	S.push(3);
	
	cout<<S<<'\n';
	
	return 0;
}
