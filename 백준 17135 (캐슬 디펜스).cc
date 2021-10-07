#include<iostream>
#include<algorithm>
#include<queue>
#include<cmath>
#include<memory.h>

using namespace std;

int n,m,d; // 세로,가로,사거리.
int arr[20][20];
int archer[4]; //3명의 궁수 배치할 곳.
int num_enemy = 0; //적의 수.
int dy[4] = {-1,0,1,0};       
int dx[4] = {0,-1,0,1};
bool picked[20]= {false}; //뽑힌 궁수.
bool dead[20][20] = {false};
int max_val = 0;
bool compare(const pair<int,int> &a,const pair<int,int> &b)
{
  return a.second < b.second; //x값이 작은게 먼저 옴.
}
void bfs(int y,int x) 
{
  bool visited[20][20]={false};
  vector<pair<int,int>> v; //잡은적.
  queue<pair<int,int>> q; 
  q.push(make_pair(y,x));
  visited[y][x] = true; //시작점 방문.
  int dist = 0;
  while(!q.empty())
  {
    if(dist>=d) //사정거리보다 길면.
    {
      return;
    }
    int q_size = q.size();
    while(q_size-->0) //같은 너비.
    {
      int cur_y = q.front().first;
      int cur_x = q.front().second;
      q.pop();
      for(int i=0;i<4;i++)
      {
        int ny = cur_y + dy[i];
        int nx = cur_x + dx[i];
        if(ny<1 || nx<1 || ny>n || nx>m) //범위 제한.
          continue;
        if(!visited[ny][nx] && arr[ny][nx]==0) //빈 칸.
        {
          visited[ny][nx] = true;
          q.push(make_pair(ny,nx)); 
        }
        else if(!visited[ny][nx] && arr[ny][nx]==1) //적.
        {
          visited[ny][nx] = true;
          v.push_back(make_pair(ny,nx));
        }
      }
    }
    if(v.size()!=0) //적을 잡았으면.
    {
      sort(v.begin(),v.end(),compare);
      dead[v[0].first][v[0].second] = true; //이칸에 있는 놈 죽는다.
      return;
    }
    dist++;    
  }  
  return;                        
}         
void dfs(int id,int cnt)
{
  if(cnt==3)
  {
    int copy_arr[20][20];
    int copy_enemy = num_enemy; //적의 수 복사.
    memcpy(copy_arr,arr,sizeof(arr)); //배열 복구용.
    int kill = 0; //죽인놈.
    while(num_enemy>0) //적이 살아 있으면.
    {
      bfs(n+1,archer[0]);
      bfs(n+1,archer[1]);
      bfs(n+1,archer[2]);
      for(int i=1;i<=n;i++)
      {
        for(int j=1;j<=m;j++)
        {
          if(dead[i][j])
          {
            arr[i][j] = 0; //죽임.
            kill++;
            num_enemy--;
          }
        }
      }
      for(int i=1;i<=m;i++) //맨밑에칸에서 안죽고 넘어가는 적.
      {
        if(arr[n][i]==1)
          num_enemy--;
      }
      for(int i=1;i<=m;i++) //한칸씩 내리기.
      {
        for(int j=n;j>1;j--)
        {
          arr[j][i] = arr[j-1][i];
        }
        arr[1][i] = 0; //맨 위에칸은 0.
      }
      memset(dead,false,sizeof(dead)); //죽이는 배열 초기화.
    }
    num_enemy = copy_enemy; //적의 수 복구.
    memcpy(arr,copy_arr,sizeof(arr)); //배열 복구.
    max_val = max(max_val,kill);
    return;
  }
  for(int i=id;i<=m;i++) //조합.
  {
    if(!picked[i])
    {
      picked[i] = true;
      archer[cnt] = i;
      dfs(i+1,cnt+1);
      picked[i] = false;
    }
  }
}                            
int main()                            
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  cin >> n >> m >> d;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      cin >> arr[i][j];
      if(arr[i][j]==1)
        num_enemy++;
    }
  }
  dfs(1,0);
  cout << max_val;
  return 0;
}
///4 3 2 3 4 
///3 2 1 2 3  
///2 1 0 1 2  