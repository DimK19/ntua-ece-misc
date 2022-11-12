#include<iostream>

using namespace std;

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