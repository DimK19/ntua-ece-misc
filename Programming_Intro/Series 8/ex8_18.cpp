#include<cstdio>

using namespace std;

class queue
{
    public:
		queue();
		bool empty();
		void enqueue(int x);
		int first();
		void pop();

	private:
		struct node
		{
			int value;
			node *next;
		};

		node *front, *rear;
};

queue::queue()
{
	front = rear = nullptr;
}

bool queue::empty()
{
	return front == nullptr;
}

void queue::enqueue(int x)
{
	node *p = new node;
	p->value = x;
	p->next = nullptr;

	if(front == nullptr) front = p;
	else rear->next = p; // links to the previously last node

	rear = p; // updates rear pointer
}

int queue::first()
{
	return front->value;
}

void queue::pop()
{
	if(front == rear) rear = nullptr;

	node *p = front;
	front = front->next;
	delete p;
}

int main()
{
	int n, poscount, negcount;
	queue PQ, NQ; // positive, negative
	bool flag = true;

	poscount = negcount = 0;

	while(scanf("%d", &n) == 1)
	if(n > 0)
	{
		PQ.enqueue(n);
		poscount++;
	}
	else
	{
		NQ.enqueue(-n);
		negcount++;
	}
	
	// compare queues
	 
	if(poscount != negcount) flag = false;
	else
		while(!PQ.empty() && !NQ.empty())
		{
			if(PQ.first() != NQ.first())
			{
				flag = false;
				break;
			}
			PQ.pop();
			NQ.pop();
		}
          
	if(flag) printf("yes\n");
	else printf("no\n");

	return 0;
}
