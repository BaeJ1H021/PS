#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n,m;
long double arr[500];
long double min_val = 121110987654321;
void dfs(int num)
{
  for(int i=0;i<=n-num;i++)
  {//분산구하기. 제평평제.
    long double sum1=0;
    long double sum2=0;
    for(int j=0;j<num;j++)
    {
      //제곱의평균.
      sum1+= arr[i+j]*arr[i+j];
      //평균의 제곱.
      sum2+= arr[i+j];
    }
    sum1 /= (long double)num;
    sum2 /= (long double)num;  
    sum2 *= (long double)sum2;
    long double result = sqrt(sum1-sum2);
    min_val = min(min_val,result);
  }
}
int main()
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> n >> m;
  for(int i=0;i<n;i++)
    cin >> arr[i];
  for(int i=m;i<=n;i++)
    dfs(i);
  cout <<fixed ;
  cout.precision(11);
  cout <<min_val;
  return 0;
}