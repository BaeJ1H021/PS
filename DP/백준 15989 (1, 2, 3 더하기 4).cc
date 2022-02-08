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

  int T;
  cin >> T;

  int arr[10001][4];
  //겹치는 경우의 수를 제외, 따라서 오름차순만 카운트해준다.
  arr[1][1] = 1; //1
  arr[2][1] = 1; //11
  arr[2][2] = 1; //2
  arr[3][1] = 1; //111
  arr[3][2] = 1; //12
  arr[3][3] = 1; //3

  for(int i=4;i<=10000;i++)
  {
    arr[i][1] = arr[i-1][1];
    arr[i][2] = arr[i-2][1]+arr[i-2][2];
    arr[i][3] = arr[i-3][1]+arr[i-3][2]+arr[i-3][3];   
  }

  while(T-->0)
  {
    int n;
    cin >> n;
    cout << arr[n][1] + arr[n][2] + arr[n][3] << "\n";
  }

  return 0;
}