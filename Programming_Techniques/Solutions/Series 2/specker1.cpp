#include<stdexcept>

using namespace std;

class Move
{
	private:
		int source_heap, source_coins, target_heap, target_coins;
		
	public:
		// take sc coins from heap sh and put tc coins to heap th
		Move(int sh, int sc, int th, int tc);
		
		int getSource() const;
		int getSourceCoins() const;
		int getTarget() const;
		int getTargetCoins() const;
	
		friend ostream& operator<<(ostream &out, const Move &move);
};

class State
{
	private:
		int *p;
		int maxHeaps, totalCoins = 0;
	
	public:
		// State with h heaps, where heap #i starts with c[i] coins
		State(int h, const int c[]);
		~State();
		
		void next(const Move &move) throw(logic_error);
		bool winning() const;
		
		int getHeaps() const;
		int getCoins(int h) const throw(logic_error);
		
		friend ostream& operator<<(ostream &out, const State &state);
};

Move::Move(int sh, int sc, int th, int tc)
{
	source_heap = sh;
	source_coins = sc;
	target_heap = th;
	target_coins = tc;
}

int Move::getSource() const
{
	return source_heap;
}

int Move::getSourceCoins() const
{
	return source_coins;
}

int Move::getTarget() const
{
	return target_heap;
}

int Move::getTargetCoins() const
{
	return target_coins;
}

ostream& operator<<(ostream &out, const Move &move)
{
	out<<"takes ";
	if(move.source_coins == 0) out<<"nothing ";
	else out<<move.source_coins<<" coins ";
	out<<"from heap "<<move.source_heap<<" and puts ";
	if(move.target_coins == 0) out<<"nothing";
	else out<<move.target_coins<<" coins to heap "<<move.target_heap;
	
	return out;
}

State::State(int h, const int c[])
{
	p = new int[h];
	maxHeaps = h;
	for(int i = 0; i < h; ++i)
	{
		p[i] = c[i];
		totalCoins += p[i];
	}
}

State::~State()
{
	delete[] p;
}

void State::next(const Move &move) throw(logic_error)
{
	if(move.getSource() < 0 || move.getSource() > maxHeaps || move.getTarget() < 0 || move.getTarget() > maxHeaps || move.getSourceCoins() <= move.getTargetCoins()) throw logic_error("invalid heap");
	if(p[move.getSource()] < move.getSourceCoins()) throw logic_error("invalid heap");
	p[move.getSource()] -= move.getSourceCoins();
	p[move.getTarget()] += move.getTargetCoins();
	totalCoins = totalCoins - move.getSourceCoins() + move.getTargetCoins();
}

bool State::winning() const
{
	return totalCoins == 0;
}

int State::getHeaps() const
{
	return maxHeaps;
}

int State::getCoins(int h) const throw(logic_error)
{
	if(h < 0 || h >= maxHeaps) throw logic_error("invalid heap");
	
	return p[h];
}

ostream& operator<<(ostream &out, const State &state)
{
	for(int i = 0; i < state.maxHeaps - 1; ++i) out<<state.p[i]<<", ";
	out<<state.p[state.maxHeaps - 1];
	
	return out;
}
