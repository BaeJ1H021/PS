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

int v,e;
int from,to;
//그래프의 인접리스트 표현.
vector<int> vec[10001];
// 정점의 발견순서. 처음에는 -1로 초기화.
int visited[10001];
//컴포넌트 번호.
int scc_id[10001];
//정점의 번호를 담는 스택.
stack<int> st;
//인덱스.
int order = 0;
//컴포넌트 인덱스.
int scc_cnt = 0;
//컴포넌트를 하나의 노드로 보는 새 그래프.
vector<int> new_graph[10001];
//컴포넌트에 들어있는 노드의 수.
int com_size[10001];
//정답 저장하는 dp.
int dp[10001];
//새로은 그래프의 시작점에서부터 bfs.
void bfs()
{
  int start = scc_id[from];
  int end = scc_id[to];
  //시작도시와 끝도시가 같은 컴포넌트면.
  if(start == end)
  {
    cout << com_size[start];
    return;
  }

  queue<int> q;
  q.push(start);
  dp[start] = com_size[start];
  while(!q.empty())
  {
    int now = q.front();
    q.pop();

    for(int i=0;i<new_graph[now].size();i++)
    {
      int next = new_graph[now][i];
      if(dp[next] < dp[now] + com_size[next])
      {
        dp[next] = dp[now] + com_size[next];
        q.push(next);
      }
    }
  }
  cout << dp[end];
}
//SCC를 찾는 타잔 알고리즘.
int scc(int here)
{
  //ret은 here에서 방문 가능한 가장 높은 정점의 번호.
  int ret = visited[here] = order++;
  //스택에 here을 넣으면 here의 후손들은 모두 스택에서 here 후에 들어간다.
  st.push(here);
  for(int i=0;i<vec[here].size();i++)
  {
    int next = vec[here][i];
    //가본적 없으면.
    if(visited[next]==-1)
      ret = min(ret, scc(next));
    else if(scc_id[next]==-1)
      ret = min(ret, visited[next]);
  }
  // here에서 부모로 올라가는 간선을 끊어야 할 지 확인.
  if(ret == visited[here])
  {
    //here를 루트로 하는 서브트리에 정점들을 컴포넌트로 묶는다.
    while(true)
    {
      com_size[scc_cnt]++;
      int t = st.top();
      st.pop();
      scc_id[t] = scc_cnt;
      if(t == here)
        break;
    }
    scc_cnt++;
  }
  return ret;
}
int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  memset(visited,-1,sizeof(visited));
  memset(scc_id,-1,sizeof(scc_id));
  
  cin >> v >> e >> from >> to;
  for(int i=1;i<=e;i++)
  {
    int a,b;
    cin >> a >> b;
    vec[a].push_back(b);
  }
  for(int i=1;i<=v;i++)
  {
    if(visited[i] == -1)
      scc(i);
  }

  for(int i=1;i<=v;i++)
  {
    for(int j=0;j<vec[i].size();j++)
    {
      int next = vec[i][j];
      if(scc_id[i]!=scc_id[next])
      {
        new_graph[scc_id[i]].push_back(scc_id[next]);
      }
    }
  }
  bfs();
  return 0;
}