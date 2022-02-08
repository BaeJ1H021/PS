#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>

using namespace std;
int dp[301]; 
int arr[301];
int main()                            
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  
  for(int i=1;i<=n;i++)
    cin >> arr[i];
  dp[1] = arr[1];
  dp[2] = arr[1]+arr[2];
  for(int i=3;i<=n;i++) //i번 계단 밟는 것.
  {
    dp[i] = max(dp[i-3]+arr[i-1],dp[i-2])+arr[i];  
  }
  cout << dp[n];
  return 0;
}
