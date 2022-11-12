#include<iostream>

using namespace std;

template<typename T>
class stack
{
	private:
		T *arr;
		int top, stsize;

	public:
		stack(int size)
		{
			stsize = size;
			arr = new T[stsize];
			top = 0;
		}

		stack(const stack &s)
		{
			stsize = s.stsize;
			arr = new T[stsize];
			for(int i = 0; i < s.top; ++i) arr[i] = s.arr[i];
			top = s.top;
		}

		~stack()
		{
			delete[] arr;
		}

		const stack& operator=(const stack &s)
		{
			delete[] arr;
			arr = new T[s.stsize];
			top = s.top;
			for(int i = 0; i < top; ++i) arr[i] = s.arr[i];
			return *this;
		}

		bool empty()
		{
			return top == 0;
		}

		void push(const T &x)
		{
			arr[top++] = x;
		}

		T pop()
		{
			return arr[--top];
		}																 
		int size()
		{
			return top;
		}
		
		friend ostream& operator<<(ostream &out, const stack &s)
		{
			if(s.top == 0) out<<"[]";
			else
			{
			 out<<'[';
			 for(int i = 0; i < s.top - 1; ++i) out<<s.arr[i]<<", ";
			 out<<s.arr[s.top - 1]<<']';
			}
			return out;
		}
};
