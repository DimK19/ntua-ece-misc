#include<iostream>
#include<queue>

using namespace std;

int main()
{
	queue<int> PQ, NQ;
	int n, poscount, negcount;
	bool flag = true;

	poscount = negcount = 0;

	while(cin>>n)
		if(n > 0)
		{
			PQ.push(n);
			poscount++;
		}
		else
		{
			NQ.push(-n);
			negcount++;
		}

	// compare queues  

	while(!PQ.empty() && !NQ.empty())
	{
		if(PQ.front() != NQ.front())
		{
			flag = false;
			break;
		}
		PQ.pop(); NQ.pop();
	}	

	if(poscount == negcount && flag) cout<<"yes\n";
	else cout<<"no\n";

	return 0;
}
