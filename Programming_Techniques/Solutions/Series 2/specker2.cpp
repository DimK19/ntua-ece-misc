#include<iostream>
#include<string>

using namespace std;

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
