#include<iostream>
#include<algorithm>
#ifndef CONTEST
#include"fullratio.hpp"
#endif

using namespace std;

int rational::gcd(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while(a > 0 && b > 0)
      if(a > b) a = a % b;
      else b = b % a;
          
    return (a + b);
}

rational::rational(int n, int d)
{
    int g = gcd(n, d);
    nom = n / g;
    den = d / g;
    if(den < 0)
    {
      nom = - nom;
      den = - den;
    }
}

rational operator+(const rational &x, const rational &y)
{
    int n = x.nom * y.den + y.nom * x.den;
    int d = x.den * y.den;
    rational sum(n, d);
                
    return sum;
}

rational operator-(const rational &x, const rational &y)
{
    int n = x.nom * y.den - y.nom * x.den;
    int d = x.den * y.den;
    rational diff(n, d);
                
    return diff;
}

rational operator*(const rational &x, const rational &y)
{
    int n = x.nom * y.nom;
    int d = x.den * y.den;
    rational prod(n, d);
                
    return prod;
}

rational operator/(const rational &x, const rational &y)
{
    int n = x.nom * y.den;
    int d = x.den * y.nom;
    rational quot(n, d);
                
    return quot;
}

std::ostream& operator<<(std::ostream &out, const rational &x)
{
    out<<x.nom<<'/'<<x.den;
    return out;
}
