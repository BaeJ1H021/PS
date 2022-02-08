#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>
#include<stack>
#include<map>

#define INF 2e9

using namespace std;

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int r,c,w;
  cin >> r >> c >> w;

  int arr[31][31] = {0};
  arr[1][1] = 1;

  for(int i=2;i<=30;i++)
  {
    for(int j=1;j<=i;j++)
    {
      arr[i][j] = arr[i-1][j-1]+arr[i-1][j];
    }
  }

  int sum = 0;

  for(int i=0;i<w;i++)
  {
    for(int j=0;j<=i;j++)
    {
      sum += arr[r+i][c+j];
    }
  }
  
  cout << sum;

  return 0;
}