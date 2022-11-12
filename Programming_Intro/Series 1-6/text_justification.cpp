#include<iostream>
#include<string>
//#include<fstream>

using namespace std;

//ifstream in("formatin.txt");
//ofstream out("formatout.txt");

void format(string &str)
{
	int spaces[30];
	int k = 0;
	int size = str.length();
	while(str[size-1] == ' ')
	{
		str.pop_back();
		size--;
	}

	for(int i = 0; i < size; ++i) if(str[i] == ' ') spaces[k++] = i;

	// spaces[i] is the position of the i-th gap
	// k is equal to the number of spaces between the words

	int extraspaces = 60 - size;
	int addtoall = extraspaces / k; // num of spaces to add to all gaps
	int rem = extraspaces % k; // add one space to the last rem gaps

	string addition = "";  
	while(addtoall--) addition += ' ';
	
	for(int i = k - 1; i >= 0; --i) str.insert(spaces[i], addition);

	size = str.length(); // update with new length
	k = 0;
	for(int i = size - 1; i > 0; --i) if(str[i] != ' ' && str[i-1] == ' ') spaces[k++] = i;
	
	k = 0;
	while(rem--) str.insert(spaces[k++], " ");
}

int main()
{
	char c, previous = '@';
	string text = "", word = "", line = "", finaltext = "";

	c = cin.get();
	while(c != EOF)
	{
		if(c != '\n' && c != ' ')
		{
			text += c;
			previous = c;
		}
		if(c == ' ' && previous != ' ' && previous != '\n')
		{
			text += c;
			previous = c;
		}
		if(c == '\n' && previous != '\n')
		{
			text += ' ';
			previous = '\n';
		}

		c = cin.get();
	}

	int size = text.length();
	for(int i=0; i<size; ++i)
	{
		if(i == size - 1) word += text[i];
		else if(text[i] != ' ')
		{
			word += text[i];
			continue;
		}

		// space found

		if(word.length() + line.length() <= 60)
		{
			line.append(word);
			word = "";

			if(line.length() < 60) line += ' ';
		}
		else
		{
			format(line);
			finaltext.append(line);
			finaltext += '\n';
			line = word + ' ';
			word = "";
		}
	}

	finaltext.append(line);
	int fsize = finaltext.length();
	while(finaltext[fsize-1] == ' ')
	{
		finaltext.pop_back();
		fsize--;
	}
	cout<<finaltext<<'\n';

	return 0;
}
