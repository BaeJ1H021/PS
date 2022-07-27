#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>

using namespace std;

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  string s1;
  string s2;

  cin >> s1;
  cin >> s2;

  while(s2.length()>s1.length())
  {
    if(s2[s2.length()-1]=='A')
      s2 = s2.substr(0,s2.length()-1);
    else
    {
      s2 = s2.substr(0,s2.length()-1);
      reverse(s2.begin(),s2.end());
    }
  }
  if(s1==s2)
    cout << 1;
  else
    cout << 0;
  return 0;
} 