#include<iostream>
#include<stdexcept>
#include<exception>
#include<iomanip>

using namespace std;

class ChessBoardArray
{
	protected:
		int *data;
		unsigned size, base;

		class Row
		{
			private:
				ChessBoardArray &cba;
				int row;
														
			public:
				Row(ChessBoardArray &a, int i) : cba(a), row(i) {}
				int& operator[](int i) const
				{
					return cba.select(row, i);
				}
		};
					  
		class ConstRow
		{
			private:
				const ChessBoardArray &cba;
				int row;
			
			public:
				ConstRow(const ChessBoardArray &a, int i) : cba(a), row(i) {}
				int operator[](int i) const
				{
					return cba.select(row, i);
				}
		};
						
	public:
		ChessBoardArray(unsigned usize = 0, unsigned ubase = 0) : data(new int[(usize * usize + 1) / 2]), size(usize), base(ubase)
		{
			for(int i = 0; i < (size * size + 1) / 2; ++i) data[i] = 0;
		}

		ChessBoardArray(const ChessBoardArray &a) : data(new int[(a.size * a.size + 1) / 2]), size(a.size), base(a.base)
		{
			for(int i = 0; i < (size * size + 1) / 2; ++i) data[i] = a.data[i];
		}
		~ChessBoardArray();
		ChessBoardArray& operator=(const ChessBoardArray &a);
		int& select(int i, int j);
		int select(int i, int j) const;
		const Row operator[](int i);
		const ConstRow operator[](int i) const;
														
		friend ostream& operator<<(ostream &out, const ChessBoardArray &a);
		unsigned int loc(int i, int j) const throw(out_of_range);
};

ChessBoardArray::~ChessBoardArray()
{
	delete[] data;
}

ChessBoardArray& ChessBoardArray::operator=(const ChessBoardArray &a)
{
	delete[] data;
	size = a.size;
	base = a.base;
	data = new int[(size * size + 1) / 2];
	for(int i = 0; i < (size * size + 1) / 2; ++i) data[i] = a.data[i];
			  
	return *this;
}

unsigned int ChessBoardArray::loc(int i, int j) const throw(out_of_range)
{
	int ur = i - base, uc = j - base;
	if(ur < 0 || ur >= size || uc < 0 || uc >= size || (i + j) % 2) throw out_of_range("invalid index");
	 
	return (ur * size + uc) / 2;
}

int& ChessBoardArray::select(int i, int j)
{
	return data[loc(i, j)];
}

int ChessBoardArray::select(int i, int j) const
{
	return data[loc(i, j)];
}

const ChessBoardArray::Row ChessBoardArray::operator[](int i)
{
	return Row(*this, i);
}

const ChessBoardArray::ConstRow ChessBoardArray::operator[](int i) const
{
	return ConstRow(*this, i);
}

ostream& operator<<(ostream &out, const ChessBoardArray &a)
{
	for(int i = a.base; i < a.size + a.base; ++i)
	{
		for(int j = a.base; j < a.size + a.base; ++j)
			try
			{
				out<<setw(4)<<a.data[a.loc(i, j)];
			}
			catch(out_of_range &e)
			{
				out<<setw(4)<<'0';
			}
			
		out<<'\n';
	}

	return out;
}
/*
int main()
{
	ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
	a[3][1] = 42;
	a[4][4] = 17;

	try
	{
		a[2][1] = 7;
	}
	catch(out_of_range &e)
	{
		cout<<"a[2][1] is black\n";
	}
								 
	try
	{
		cout<<a[1][2]<<'\n';
	}
	catch(out_of_range &e)
	{
		cout<<"and so is a[1][2]\n";
	}

	cout<<a;

	return 0;
}*/

