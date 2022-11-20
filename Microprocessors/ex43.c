#include<avr/io.h>

int main(void)
{
	char x;
	DDRA = 0x00; // Initialize port A for input
	DDRB = 0xFF; // Initialize port B for output

	x = 1; // Initialize variable for active LED
	PORTB = x;
	
    while(1)
    {
		switch(PINA & 0x0F) // bitwise AND with eight 1's, only one will stay on
		{
			case 1:
				// SW0 slide left
				while((PINA & 0x0F) == 1); // wait until push button is released
				// if the LED is at the left-most position (128), move it to the right-most, else shift left
				if(PORTB == 0x80) PORTB = 1;
				else PORTB <<= 1;
				break;
			case 2:
				// SW1 slide right
				while((PINA & 0x0F) == 2); // wait until push button is released
				// if the LED is at the right-most position (128), move it to the left-most, else shift right
				if(PORTB == 1) PORTB = 0x80;
				else PORTB >>= 1;
				break;
			case 4:
				// SW3 slide left by 2
				while((PINA & 0x0F) == 4); // wait until push button is released
				if(PORTB == 0x80) PORTB = 2;
				else if(PORTB == 0x40) PORTB = 1;
				else PORTB <<= 2;
				break;
			case 8:
				// SW4 move to MSB (LED 7)
				while((PINA & 0x0F) == 8); // wait until push button is released
				PORTB = 0x80;
				break;
		}
    }
}
