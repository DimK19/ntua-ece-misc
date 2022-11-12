#include<iostream>
#include<stdlib.h>

using namespace std;

int euclid(int a, int b)
{
	if(a==0 || b==0)	return (a+b);
	else if(a>b)	return euclid(b, a%b);
	else	return euclid(a, b%a);
}

int main()
{
	long long int N, num1, num2, den1, den2, fnum, fden, gcd, integer_part, temp1, temp2;
	char operation;
	
	cin >> N;
	
	for(int i=0; i<N; ++i)
	{
		cin>>operation;
		cin>>num1>>den1>>num2>>den2;
		
		if(den1==0 || den2==0)
		{
			cout<<"error\n";
			continue;
		}
		
		switch(operation)
		{
			case '+':
				fnum = num1 * den2 + num2 * den1;
				fden = den1 * den2;
				break;
				
			case '-':
				fnum = num1 * den2 - num2 * den1;
				fden = den1 * den2;
				break;
				
			case '*':
				fnum = num1 * num2;
				fden = den1 * den2;
				break;
				
			case '/':
				if(num2==0)
				{
					cout<<"error\n";
					continue;
				}
				fnum = num1 * den2;
				fden = den1 * num2;
				break;
				
			default:
				std::cout<<"error\n";
				continue;
		}
		
		temp1 = abs(fnum);
		temp2 = abs(fden);
		
		gcd = euclid(temp1, temp2);
		
		fden /= gcd;
		fnum /= gcd;
		
		integer_part = fnum / fden;
		fnum -= integer_part * fden;
		if(integer_part==0 && fnum*fden<0)	cout<<'-';
		cout<<integer_part<<' '<<abs(fnum)<<' '<<abs(fden)<<'\n';
	}
	
	return 0;
}
