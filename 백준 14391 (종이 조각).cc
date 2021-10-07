#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

int n,m;
int arr[4][4];
bool visited[4][4] = {false};
int answer = 0;
void dfs(int y,int x,int sum)
{
  if(y==n) //다 했을때.
  {
    answer = max(answer,sum);
    return;
  }
  if(x==m)
  {
    dfs(y+1,0,sum);
    return;
  }
  if(!visited[y][x]) //방문하지 않은 곳이면.
  {
    visited[y][x] = true; // 이칸은 백트래킹을 해도 트루여야함.
    dfs(y,x+1,sum + arr[y][x]); //해당칸만 포함하는거.
    bool copy_visit[4][4];
    memcpy(copy_visit,visited,sizeof(visited)); //백트래킹용.
    for(int i=y+1;i<n;i++) //밑으로.
    {
      int mul = arr[y][x];
      if(!visited[i][x]) //방문한 곳이 아니면.
      {
        for(int j=y+1;j<=i;j++)
        {
          mul *=10;
          mul +=arr[j][x];   
        }
        visited[i][x] = true;
        dfs(y,x+1,sum+mul);
      }
      else 
        break;  
    }
    memcpy(visited,copy_visit,sizeof(visited)); //전으로 돌려놓기.
    for(int i=x+1;i<m;i++) //옆으로.
    {
      int mul = arr[y][x];
      if(!visited[y][i]) //방문한 곳이 아니면.
      {
        for(int j=x+1;j<=i;j++)
        {
          mul *= 10;
          mul += arr[y][j];
        }
        visited[y][i] = true;
        dfs(y,x+1,sum+mul);
      }
      else
        break;
    }
    memcpy(visited,copy_visit,sizeof(visited)); //전으로 돌려놓기.
    visited[y][x] = false; //이칸을 안밟은것으로 백트래킹. 
  }
  else //방문했던 곳이면.
    dfs(y,x+1,sum);
}
int main()
{
  cin >> n >> m;
  for(int i=0;i<n;i++)
  {
    string str;
    cin >> str;
    for(int j=0;j<m;j++)
      arr[i][j] = str[j]-'0';
  }
  dfs(0,0,0);
  cout << answer;
  return 0;
}