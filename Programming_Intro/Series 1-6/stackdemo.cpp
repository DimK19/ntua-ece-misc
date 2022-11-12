#include<iostream>

using namespace std;

template<typename T>
class stack
{
	public:
		stack(int size);
		stack(const stack &s);
		~stack(int size);
		const stack& operator=(const stack &s);
		bool empty();
		void push(const T &x);
		T top();
		void pop();
		int size();
		friend ostream operator<<(ostream &out, const stack &s);
	
	private:
		struct node
		{
			T value;
			node *next;
		};
		
		node *top;
};

	
