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

int arr[1000001];

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  int b,c;
  cin >> n;
  for(int i=1;i<=n;i++)
  {
    cin >> arr[i];
  }
  cin >> b >> c;

  long long ans = 0;
  for(int i=1;i<=n;i++)
  {
    arr[i] -= b; //총감독관.
    ans++;
    if(arr[i]>0)
    {
      if(arr[i]%c==0) //나누어 떨어지면.
        ans += arr[i]/c;
      else
        ans += arr[i]/c + 1;
    }
  }
  cout << ans;
  return 0;
}