#include<iostream>
#include<cmath>

using namespace std;

class Polynomial
{
	protected:
		class Term
		{
			protected:
				int exp, co;
				Term *next;
				Term(int e, int c, Term *n)
				{
					exp = e;
					co = c;
					next = n;
				}

				friend class Polynomial;
				
				friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
				friend Polynomial operator*(const Polynomial &p, const Polynomial &q);
				friend ostream& operator<<(ostream &out, const Polynomial &p);
		};
		
		Term *first;

	public:
		Polynomial();
		Polynomial(const Polynomial &p);
		~Polynomial();
		Polynomial& operator=(const Polynomial &p);
						  
		void addTerm(int e, int c);
		double evaluate(double x);

		friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
		friend Polynomial operator*(const Polynomial &p, const Polynomial &q);
		friend ostream& operator<<(ostream &out, const Polynomial &p);
};

Polynomial::Polynomial()
{
	first = nullptr;
}

Polynomial::Polynomial(const Polynomial &p)
{
	if(p.first == nullptr)
	{
		first = nullptr;
		return;
	}
	first = new Term(p.first->exp, p.first->co, nullptr);
	Term *it = p.first->next;
	Term *pf = first;
	while(it != nullptr)
	{
		Term *temp = new Term(it->exp, it->co, nullptr);
		pf->next = temp;
		pf = pf->next;
		it = it->next;
	}
}

Polynomial::~Polynomial()
{
	while(first != nullptr)
	{
		Term *it = first;
		first = first->next;
		delete it;
	}
}

Polynomial& Polynomial::operator=(const Polynomial &p)
{
	while(first != nullptr)
	{
		Term *it = first;
		first = first->next;
		delete it;
	}
	
	if(p.first == nullptr)
	{
		first = nullptr;
		return *this;
	}
	
	first = new Term(p.first->exp, p.first->co, nullptr);
	Term *it = p.first->next;
	Term *pf = first;
	while(it != nullptr)
	{
		Term *temp = new Term(it->exp, it->co, nullptr);
		pf->next = temp;
		pf = pf->next;
		it = it->next;
	}
			  
	return *this;
}

void Polynomial::addTerm(int e, int c)
{
	if(first == nullptr)
	{
		first = new Term(e, c, nullptr);
	}
	else if(first->exp == e)
	{
		first->co += c;
		if(first->co == 0)
		{
			Term *t = first;
			first = first->next;
			delete t;
		}
	}
	else if(e > first->exp)
	{
		Term *t = new Term(e, c, first);
		first = t;
	}
	else
	{
		Term *left, *right;
		left = first;
		right = first->next;
		while(left->exp > e)
		{
			if(right == nullptr)
			{
				Term *t = new Term(e, c, right);
				left->next = t;
				break;
			}
			else if(right->exp < e)
			{
				Term *t = new Term(e, c, right);
				left->next = t;
				break;
			}
			else if(right->exp == e)
			{
				right->co += c;
				if(right->co == 0)
				{
					left->next = right->next;
					delete right;
				}
				break;
			}
										 
			left = left->next;
			right = right->next;
		}
	}
}

double Polynomial::evaluate(double x)
{
	double value = 0;
	Term *it = first;
	while(it != nullptr)
	{
		value += it->co * pow(x, it->exp);
		it = it->next;
	}
		  
	return value;
}

Polynomial operator+(const Polynomial &p, const Polynomial &q)
{
	Polynomial r = p;
	Polynomial::Term *it = q.first;
	while(it != nullptr)
	{
		r.addTerm(it->exp, it->co);
		it = it->next;
	}
		  
	return r;
}

Polynomial operator*(const Polynomial &p, const Polynomial &q)
{
	Polynomial::Term *t1 = p.first;
	Polynomial::Term *t2 = q.first;
	Polynomial r;
	while(t1 != nullptr)
	{
		while(t2 != nullptr)
		{
			r.addTerm(t1->exp + t2->exp, t1->co * t2->co);
			t2 = t2->next;
		}
		
		t2 = q.first;
		t1 = t1->next;
	}
			
	return r;
}

ostream& operator<<(ostream &out, const Polynomial &p)
{
	Polynomial::Term *it = p.first;
	if(it == nullptr)
	{
		out<<'0';
		return out;
	}
	
	while(it != nullptr)
	{
		int cf = abs(it->co);
		if(it == p.first && it->co < 0) out<<"- ";
		if(it->exp == 0) out<<cf;
		else if(it->exp == 1)
		{
			if(cf == 1) out<<'x';
			else out<<cf<<'x';
		}
		else
		{
			if(cf == 1) out<<"x^"<<it->exp;
			else out<<cf<<"x^"<<it->exp;
		}

		if(it->next != nullptr)
		{
			if(it->next->co > 0) out<<" + ";
			else out<<" - ";
		}

		it = it->next;
	}
	
	return out;
}

#ifndef CONTEST

int main()
{
	Polynomial p;
	Polynomial q;
	
	p = q;
	/*
	p.addTerm(1, 1);
	p.addTerm(0, -1);

	cout << '"' << p << '"' << endl;
	cout << '"' << p.evaluate(0) << '"' << endl;
	cout << '"' << p.evaluate(1) << '"' << endl;
	cout << '"' << p.evaluate(15) << '"' << endl;
	cout << '"' << p.evaluate(1500) << '"' << endl;

	Polynomial q;
	  
	q.addTerm(1, 1);
	q.addTerm(0, 1);

	cout << '"' << q << '"' << endl;
	cout << '"' << q.evaluate(0) << '"' << endl;
	cout << '"' << q.evaluate(1) << '"' << endl;
	cout << '"' << q.evaluate(15) << '"' << endl;
	cout << '"' << q.evaluate(1500) << '"' << endl;

	Polynomial psum(p + q);

	cout << '"' << psum << '"' << endl;
	cout << '"' << psum.evaluate(0) << '"' << endl;
	cout << '"' << psum.evaluate(1) << '"' << endl;
	cout << '"' << psum.evaluate(15) << '"' << endl;
	cout << '"' << psum.evaluate(1500) << '"' << endl;
	
	Polynomial pmul;

	pmul = p * q;

	cout << '"' << pmul << '"' << endl;
	cout << '"' << pmul.evaluate(0) << '"' << endl;
	cout << '"' << pmul.evaluate(1) << '"' << endl;
	cout << '"' << pmul.evaluate(15) << '"' << endl;
	cout << '"' << pmul.evaluate(1500) << '"' << endl;
*/
	return 0;
}

#endif
