#include<stdexcept>
#include<iostream>
#include<string>

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

class Player
{
    protected:
        string *name;
              
    public:
        Player(const string &n);
        virtual ~Player();
        string getName() const;

        virtual const string& getType() const = 0;
        virtual Move play(const State &s) = 0;

        friend ostream& operator<<(ostream &out, const Player &player);
};

Player::Player(const string &n)
{
    name = new string(n);
}

string Player::getName() const
{
    return *name;
}

ostream& operator<<(ostream &out, const Player &player)
{
    out<<player.getType()<<" player "<<player.getName();
      
    return out;
}

Player::~Player()
{
    delete name;
}

class GreedyPlayer : public Player
{
    private:
        string *type = new string("Greedy");
              
    public:
        GreedyPlayer(const string &n) : Player(n) {}
        ~GreedyPlayer()
        {
            delete type;
        }
                      
        const string& getType() const override
        {
            return *type;
        }
                          
        Move play(const State &s) override
        {
            int max = 0; // position of max
            for(int i = 1; i < s.getHeaps(); ++i) if(s.getCoins(max) < s.getCoins(i)) max = i;
                                                    
            return Move(max, s.getCoins(max), 0, 0);
        }
};

class SpartanPlayer : public Player
{
    private:
        string *type = new string("Spartan");
              
    public:
        SpartanPlayer(const string &n) : Player(n) {}
        ~SpartanPlayer()
        {
            delete type;
        }
                      
        const string& getType() const override
        {
            return *type;
        }
                          
        Move play(const State &s) override
        {
            int max = 0;
            for(int i = 1; i < s.getHeaps(); ++i) if(s.getCoins(max) < s.getCoins(i)) max = i;
                                                    
            return Move(max, 1, 0, 0);
        }
};

class SneakyPlayer : public Player
{
    private:
        string *type = new string("Sneaky");
              
    public:
        SneakyPlayer(const string &n) : Player(n) {}
        ~SneakyPlayer()
        {
            delete type;
        }
                      
        const string& getType() const override
        {
            return *type;
        }
                          
        Move play(const State &s) override
        {
            int min = 0;
            while(!s.getCoins(min)) ++min;
            for(int i = 1; i < s.getHeaps(); ++i) if(s.getCoins(i) && s.getCoins(min) > s.getCoins(i)) min = i;
                                                    
            return Move(min, s.getCoins(min), 0, 0);
        }
};

class RighteousPlayer : public Player
{
    private:
        string *type = new string("Righteous");
            
    public:
        RighteousPlayer(const string &n) : Player(n) {}
        ~RighteousPlayer()
        {
            delete type;
        }
                      
        const string& getType() const override
        {
            return *type;
        }
                          
        Move play(const State &s) override
        {
            int max = 0, min = 0;
            for(int i = 1; i < s.getHeaps(); ++i)
            {
                if(s.getCoins(max) < s.getCoins(i)) max = i;
                if(s.getCoins(min) > s.getCoins(i)) min = i;
            }
            
            int source = s.getCoins(max) / 2;
            if(s.getCoins(max) % 2) ++source;
            return Move(max, source, min, source - 1);
        }
};

class Game
{
    private:
        int max_heaps, max_players, hi, pi;
        int *heap_arr;
        Player **player_arr;
                      
    public:
        Game(int heaps, int players);
        ~Game();
                              
        void addHeap(int coins) throw(logic_error);
        void addPlayer(Player *player) throw(logic_error);
        void play(ostream &out) throw(logic_error);
};

Game::Game(int heaps, int players)
{
    hi = pi = 0;
    max_heaps = heaps;
    max_players = players;
    heap_arr = new int[max_heaps];
    player_arr = new Player*[max_players];
}

Game::~Game()
{
    delete[] heap_arr;
    delete[] player_arr;
}

void Game::addHeap(int coins) throw(logic_error)
{
    if(hi == max_heaps) throw logic_error("invalid heap");
    heap_arr[hi++] = coins;
}

void Game::addPlayer(Player *player) throw(logic_error)
{
    if(pi == max_players) throw logic_error("invalid heap");
    player_arr[pi++] = player;
}

void Game::play(ostream &out) throw(logic_error)
{
    if(!hi || !pi) throw logic_error("invalid heap");
    int i = 0;
    State st(max_heaps, heap_arr);
    while(!st.winning())
    {
        out<<"State: "<<st<<'\n'<<*player_arr[i % max_players]<<' '<<player_arr[i % max_players]->play(st)<<'\n';
        st.next(player_arr[i % max_players]->play(st));
        i++;
    }
    out<<"State: "<<st<<'\n'<<*player_arr[--i % max_players]<<" wins\n";
}

int main()
{
	Game specker(3, 4);
	specker.addHeap(10);
	specker.addHeap(20);
	specker.addHeap(17);
	
	specker.addPlayer(new SneakyPlayer("Alan"));
	specker.addPlayer(new SpartanPlayer("Bill"));
	specker.addPlayer(new GreedyPlayer("Charles"));
	specker.addPlayer(new RighteousPlayer("Dennis"));
	specker.play(cout);
	
	return 0;
}
