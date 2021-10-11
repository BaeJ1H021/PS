#include<iostream>
#include<queue>

using namespace std;

int n;
int max_val = 0;
int arr[10001];
queue<int> q[10];

void radixSort()
{
  int radix = 1;
  while(true)
  {
    if( radix >= max_val)
      break;
    radix *= 10;
  }

  for(int i=1;i<=radix;i*=10)
  {
    for(int j=1;j<=n;j++)
    {
      int rest = 0;

      if(arr[j]>=i)
      {
        rest = (arr[j]/i)%10; //자릿수.
      }
      q[rest].push(arr[j]);
    }

    int idx = 1;
    for(int j=0;j<10;j++)
    {
      while(!q[j].empty())
      {
        arr[idx++] = q[j].front();
        q[j].pop();
      }
    }
  }
}
int main()
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> n;
  for(int i=1;i<=n;i++)
  {
    cin >> arr[i];
    max_val = max(max_val,arr[i]);
  }

  radixSort();

  for(int i=1;i<=n;i++)
    cout << arr[i] << "\n";
  return 0;
}