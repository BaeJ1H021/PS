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

int n;
int arr[15];
vector<bool> flag;

void recur(int id,int val)
{
  //기저사례.
  if(id==n+1)
  {
    if(val>=1)
      flag[val] = true;
    return;
  }
  recur(id+1,val+arr[id]);
  recur(id+1,val-arr[id]);
  recur(id+1,val);
}

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;

  int sum = 0; //추들의 합.
  for(int i=1;i<=n;i++)
  {
    cin >> arr[i];
    sum += arr[i];
  }
  flag.resize(sum+1,false); 

  int ans = 0;
   
  recur(1,0);
  for(int i=1;i<=sum;i++)
  {
    if(!flag[i])
      ans++;
  }
  cout << ans;
  return 0;
}