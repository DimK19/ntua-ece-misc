#include<iostream>
#include<cctype>

using namespace std;

void find_sub(char *key, char *dec);
void encrypt(char *key);

int main()
{
  char key[27];
  bool found[26] = {0}, flag = true;

  cin>>key;
  cin.ignore();

  for(int i=0; i<26; ++i)
    found[key[i]-'a'] = true;

  for(int i=0; i<26; ++i)
    if(!found[i])
      flag = false;

  if(flag)
  {
    char cmd = cin.get();
    cin.ignore(256, '\n');
    if(cmd=='d')
    {
      char dec[27];
      find_sub(key, dec);
      encrypt(dec);
    }
    else
      encrypt(key);
  }
  else
    cout<<"error\n";  

  return 0;
}

void encrypt(char *key)
{
  char c;
  c = cin.get();

  while(c!=EOF)
  {
    if(c>64 && c<91)
    {
      c = tolower(c);
      c = key[c-'a'];
      c = toupper(c);
      cout<<c;
    }
    else if(c>96 && c<123)
      cout<<key[c-'a'];
    else
      cout<<c;

    c = cin.get();
  }
}

void find_sub(char *key, char *dec)
{
  for(int i=0; i<26; ++i)
    dec[key[i]-97] = (char) i+97;
}