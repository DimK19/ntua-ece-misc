#include<iostream>
#include<algorithm>
#ifndef CONTEST
#include"babyratio.hpp"
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

rational rational::add(rational r)
{
    int n = this->nom * r.den + r.nom * this->den;
    int d = this->den * r.den;
    rational sum(n, d);
                
    return sum;
}

rational rational::sub(rational r)
{
    rational neg(-r.nom, r.den);
      
    return this->add(neg);
}

rational rational::mul(rational r)
{
    int n = this->nom * r.nom;
    int d = this->den * r.den;
    rational prod(n, d);
                
    return prod;
}

rational rational::div(rational r)
{
    rational rev(r.den, r.nom);
      
    return this->mul(rev);
}

void rational::print()
{
    cout<<nom<<'/'<<den;
}
