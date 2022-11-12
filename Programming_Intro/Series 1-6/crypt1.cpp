#include<iostream>
#include<cctype>

using namespace std;

int main()
{
  char key[26], c;
  bool flag = true, found[26] = {0};

  cin>>key;
  cin.ignore();
  for(int i=0; i<26; ++i)
    found[key[i]-'a'] = true;

  for(int i=0; i<26; ++i)
    if(!found[i])
    {
      flag = false;
      break;
    }

  if(flag)
  {
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
  else
    cout<<"error\n";

  return 0;
}