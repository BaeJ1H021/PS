#include<iostream>

using namespace std;

int sorted_arr[1000001];
int arr[1000001];

void merge(int left,int right)
{
  int mid = (left+right) / 2;

  int i = left;
  int j = mid+1;
  int k = left;
  while(i<=mid && j<=right)
  {
    if(arr[i] <=arr[j])
      sorted_arr[k++] = arr[i++];
    else 
      sorted_arr[k++] = arr[j++];
  }

  int idx = (i > mid) ? j : i;

  while(k<=right) 
    sorted_arr[k++] = arr[idx++];
  for(int i=left;i<=right;i++) 
    arr[i] = sorted_arr[i];
}

void mergesort(int left,int right)
{
  if(left<right)
  {
    int mid = (left+right)/2;
    mergesort(left,mid);
    mergesort(mid+1,right);
    merge(left,right);
  }
}

int main()
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;
  for(int i=1;i<=n;i++)
    cin >> arr[i];

  mergesort(1,n);

  for(int i=1;i<=n;i++)
    cout << arr[i] << "\n";

  return 0;
}