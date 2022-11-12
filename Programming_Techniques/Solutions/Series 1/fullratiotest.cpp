#include <iostream>
#include "fullratio.hpp"

using namespace std;

int main()
{
	rational a(1, 2);
	rational b(3, 4);
	rational c(5, 6);
	cout<<a + b - c;
	cout<<a<<" should still be 1/2\n";
	
	return 0;
}
