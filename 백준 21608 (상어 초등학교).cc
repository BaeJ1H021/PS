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

int dy[4] ={-1,1,0,0};
int dx[4] ={0,0,-1,1};

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  int arr[21][21] ={0,}; //0으로 초기화.
  int love[401][4]; //i번 학생이 좋아하는 학생.
  cin >> n;
  for(int i=1;i<=n*n;i++)
  {
    int num;
    cin >> num;
    for(int j=0;j<4;j++)
    {
      cin >> love[num][j]; 
    }
  
    pair<int,int> max_id = {0,0}; //인전한 칸에 좋아하는 사람 많은.
    int max_val = -1; //좋아하는 사람 많은 칸.
    int max_blank = 0; //비어있는 칸. 
    for(int k=1;k<=n;k++)
    {
      for(int l=1;l<=n;l++)
      {
        if(arr[k][l]!=0) //사람 있으면
          continue;
        int cnt_love = 0;
        int cnt_blank = 0;
        for(int di=0;di<4;di++)
        {
          int ny = k + dy[di];
          int nx = l + dx[di];
          if(ny<1||ny>n||nx<1||nx>n)
            continue;
          for(int li=0;li<4;li++)
          {
            if(arr[ny][nx]==love[num][li])
              cnt_love++;
            else if(arr[ny][nx]==0)
              cnt_blank++;
          }
        }
        if(max_val<cnt_love)
        {
          max_val = cnt_love;
          max_id = {k,l};
          max_blank = cnt_blank;
        }
        else if(max_val==cnt_love)
        {
          if(max_blank<cnt_blank)
          {
            max_id = {k,l};
            max_blank = cnt_blank;
          }
          else if(max_blank==cnt_love) //인접한 빈칸개수도 같으면.
          {
            if(max_id.first>k) //새거가 행의 번호가 더 작으면.
            {
              max_id = {k,l};
            }
            else if(max_id.first==k) //행 번호도 같으면.
            {
              if(max_id.second>l)
                max_id = {k,l};
            }
          }
        }
      }
    }
    arr[max_id.first][max_id.second] = num; //결국 마지막에 최적의 곳에 넣는다.
  }
  
  int sum = 0;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      int cnt = 0;
      for(int di=0;di<4;di++)
      {
        int ny = i + dy[di];
        int nx = j + dx[di];
        if(ny<1||ny>n||nx<1||nx>n)
          continue;
        for(int li=0;li<4;li++)
        {
          if(arr[ny][nx]==love[arr[i][j]][li])
          {
            cnt++;
            break;
          }
        }
      }
      if(cnt==0)
        continue;
      else
        sum += pow(10,cnt-1);
    }
  }
  cout << sum;

  return 0;
}