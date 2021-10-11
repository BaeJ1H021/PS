#include<iostream>

using namespace std;

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n; //배열의 크기.
  int arr[1001];

  cin >> n;
  for(int i=1;i<=n;i++)
  {
    cin >> arr[i];
  }

  for(int i=2;i<=n;i++)
  {
    int j = i-1;  
    while(j>=1 && arr[j]>arr[j+1])
    {
      int temp = arr[j];
      arr[j] = arr[j+1];
      arr[j+1] = temp;
      j--;
    }
  }

  for(int i=1;i<=n;i++)
    cout << arr[i] << "\n";
  return 0;
}