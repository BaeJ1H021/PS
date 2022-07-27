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

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int arr[51];
  int brr[51];
  int n;
  cin >> n;
  for(int i=1;i<=n;i++)
    cin >> arr[i];

  for(int i=1;i<=n;i++)
    cin >> brr[i];
  
  sort(arr+1,arr+n+1);
  sort(brr+1,brr+n+1);

  int sum = 0;
  for(int i=1;i<=n;i++)
    sum += arr[i]*brr[n-i+1];

  cout << sum;
  return 0;
}