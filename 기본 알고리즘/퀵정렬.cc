#include<iostream>

using namespace std;

int arr[1000001];

void quickSort(int from, int to)
{
  if(from >= to)
    return;
  
  int mid = (from+to)/2;
  int pivot = arr[mid]; 
  int left = from;
  int right = to;

  while(left<=right)
  {
    while(arr[left] < pivot)
      left++;
    while(arr[right]>pivot) 
      right--;
    if(left<=right)
    {
      int temp = arr[left];
      arr[left] = arr[right];
      arr[right] = temp;
      left++;
      right--;
    } 
  }

  quickSort(from,right);
  quickSort(left,to);
}

int main()
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;

  for(int i=1;i<=n;i++)
    cin >> arr[i];

  quickSort(1,n);

  for(int i=1;i<=n;i++)
    cout << arr[i] << "\n";
  return 0;
}