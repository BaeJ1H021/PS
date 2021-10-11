#include<iostream>
#include<string>

using namespace std;

int dp[1002][1002];

int main()                            
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
 
  string s1,s2;
  cin >> s1;
  cin >> s2;
  s1 = '0' + s1;
  s2 = '0' + s2;

  for(int i=1;i<=s1.length()-1;i++)   //스트링 인덱스 주의.
  {
    for(int j=1;j<=s2.length()-1;j++)
    {
      if(s1[i]==s2[j])
        dp[i][j] = dp[i-1][j-1]+1;
      else
        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
    }
  }
  int n = s1.length()-1;
  int m = s2.length()-1;
  cout << dp[n][m] << "\n";
  string ans = "" ;
  while(dp[n][m]!=0)
  {
    if(dp[n][m]==dp[n-1][m])
      n = n-1;
    else if(dp[n][m]==dp[n][m-1])
      m = m-1;
    else 
    {
      ans = s1[n] + ans;
      n = n-1;
      m = m-1;
    }
  }
  cout << ans;
  return 0;
}