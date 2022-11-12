#include"stackdemo.cpp"
#ifndef CONTEST

int main()
{
	stack<int> s(10);
	cout<<"s is empty: "<<s<<'\n';
	s.push(1);
	cout<<"s contains one element: "<<s<<'\n';
	s.push(2);
	s.push(3);
	cout<<"s contains three elements: "<<s<<'\n';
	cout<<"size :"<<s.size()<<'\n';
	stack<int> t(5);
	t.push(4);
	cout<<"t: "<<t<<'\n';
	t = s;
	cout<<"popping from s: "<<s.pop()<<'\n';
	s.push(5);
	stack<int> a(s);
	t.push(6);
	a.push(7);
	cout<<"s: "<<s<<'\n'<<"t: "<<t<<'\n'<<"a: "<<a<<'\n';
	
	return 0;
}
#endif
