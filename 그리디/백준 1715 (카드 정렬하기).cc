#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>
#include<stack>

using namespace std;

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  priority_queue<int> pq;
  int n;
  int num;
  cin >> n;
  while(n-->0)
  {
    cin >> num;
    pq.push(-num); //오름차순 큐.
  }
  int sum = 0;
  while(pq.size()>=2)
  {
    int first = pq.top();
    pq.pop();
    int second = pq.top();
    pq.pop();
    int next = -(first+second);
    sum += next;
    pq.push(-next);
  }

  cout << sum;
  return 0;
} 