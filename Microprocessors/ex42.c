#include <avr/io.h>

int main(void)
{
	char x, f0, f1, a, b, c, d;
	DDRA = 0xFF; // Initialize port A for output
	DDRB = 0x00; // Initialize port B for input
	
	while(1)
	{
		x = PINB;
		a = x & 1; // A is the LSB
		b = (x & 2) >> 1; // B is the second to last, etc
		c = (x & 4) >> 2;
		d = (x & 8) >> 3;
		f0 = (a & b & c) | (~b & ~c & ~d);
		f1 = (a | b | c) & d;
		f0 = f0 & 1;
		f1 = (f1 << 1) & 2;
		PORTA = f0 | f1; // set output
	}
}
