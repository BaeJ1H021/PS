#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>
#include<stack>
#include<map>

using namespace std;

int arr[2010][2010]; //가중치.
int dp[2010][2010]; //출력값.

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n,m;

  char c;
  cin >> n >> m;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      cin >> c;
      arr[i][j] = c-'0'; //char -> int 변환.
    }
  }
  
  for(int j=1;j<=m;j++) //1열 -> 2열 이런식.
  {
    for(int i=1;i<=n;i++)
    {
      dp[i][j] = max(dp[i-1][j-1],max(dp[i][j-1],dp[i+1][j-1]))+arr[i][j];
    }
  }

  int max_val = 0;
  //저장 값 중 최댓값을 구하는 문제이므로
  //m-1번째 열의 출력 값중에 답이 있다.

  for(int i=1;i<=n;i++)
    max_val = max(max_val,dp[i][m-1]);
  
  cout << max_val;
  return 0;
}