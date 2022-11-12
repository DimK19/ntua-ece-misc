#include<cstdio>
#include<cmath>

bool func(int x)
{
	int digits[4], temp;
	
	temp = x;
	digits[0] = temp / 1000;
	temp %= 1000;
	digits[1] = temp / 100;
	temp %= 100;
	digits[2] = temp / 10;
	temp %= 10;
	digits[3] = temp;
	
	int sum = 0;
	for(int i=0; i<4; ++i) sum += pow(digits[i], 4);
	
	if(sum==x) return true;
	return false;
}

int main()
{
	for(int i=1000; i<10000; ++i)
	{
		if(func(i)) printf("%d\n", i);
	}
	
	return 0;
}
