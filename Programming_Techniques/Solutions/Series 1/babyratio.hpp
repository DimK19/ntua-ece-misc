class rational
{
	private:
		int num, den;
		static int gcd(int a, int b);

	public:
		rational(int n, int d);
		rational add(rational r);
		rational sub(rational r);
		rational mul(rational r);
		rational div(rational r);
		void print();
};
