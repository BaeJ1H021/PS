#include<iostream>
#include<string>

using namespace std;

int dp[4040][4040];

int main()                            
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
 
  string s1,s2;
  cin >> s1;
  cin >> s2;
  s1 = '0' + s1;
  s2 = '0' + s2;

  int ret = 0;
  for(int i=1;i<=s1.length()-1;i++)   //스트링 인덱스 주의.
  {
    for(int j=1;j<=s2.length()-1;j++)
    {
      if(s1[i]==s2[j])
        dp[i][j] = dp[i-1][j-1]+1;
      ret = max(ret,dp[i][j]);
    }
  }
  cout << ret;

  return 0;
}