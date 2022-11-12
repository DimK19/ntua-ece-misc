#include<iostream>

using namespace std;

template<typename T>
class Stack
{
	private:
		int top;
		T *arr;
	
	public:
		Stack(int size)
		{
			arr = new T[size];
			top = 0;
		}

		void push(const T &x)
		{
			arr[top++] = x;
		}
		
		int size() const
		{
			return top;
		}
		
		friend ostream& operator<<(ostream &out, const Stack &s)
		{
			// for(int i = 0; i < s.top; ++i) out<<s.arr[i]<<' '; // Works
			for(int i = 0; i < s.size(); ++i) out<<s.arr[i]<<' '; // Doesn't work
			
			return out;
		}
};
