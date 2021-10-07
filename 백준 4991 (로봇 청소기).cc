#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>

using namespace std;

char arr[21][21];
int dy[4] = {0,-1,0,1}; //서,북,동,남.
int dx[4] = {-1,0,1,0};
int m,n;
int sy,sx;
vector<pair<int,int>> v;

struct P
{
  int y;
  int x;
  int bit;
};
int getPos(int y,int x)
{
  for(int i=0;i<v.size();i++)
  {
    if(v[i].first==y && v[i].second==x)
      return i;
  }
  return 0;
}
int bfs()
{
  bool visited[21][21][1<<10];
  memset(visited,false,sizeof(visited));
  visited[sy][sx][0] = true;
  queue<P> q;
  q.push({sy,sx,0}); //시작점.
  int time = 0;
  while(!q.empty())
  {
    int q_size = q.size();
    while(q_size-->0)
    {
      int cur_y = q.front().y;
      int cur_x = q.front().x;
      int cur_bit = q.front().bit;
      q.pop();
      if(cur_bit== (1<<v.size())-1) //모든걸 다 순회.
        return time;
      for(int i=0;i<4;i++)
      {
        int ny = cur_y+dy[i];
        int nx = cur_x+dx[i];
        int nbit = cur_bit;
        if(ny<1||ny>n||nx<1||nx>m) 
          continue; 
        if(visited[ny][nx][nbit]||arr[ny][nx]=='x')
          continue;
        if(arr[ny][nx]=='*')
          nbit |= (1<<getPos(ny,nx));
        visited[ny][nx][nbit] = true;
        q.push({ny,nx,nbit});
      }
    }
    time++;
  }
  return -1;
}

int main()                            
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);

  while(true)
  {
    cin >> m >> n;
    if(m==0 && n==0)
      break;
    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=m;j++)
      {
        cin >> arr[i][j];
        if(arr[i][j]=='o')
        {
          arr[i][j] = '.'; //점을 바꿔버린다.
          sy = i;
          sx = j;
        }
        else if(arr[i][j]=='*')
        {
          v.push_back({i,j});
        }
      }
    }
    cout << bfs() << "\n";
    v.clear();
  }
  return 0;
}