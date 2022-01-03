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

//경찰서 만드는 비용.
int cost[51];
int n,v,e;
//그래프의 인접리스트 표현.
vector<int> vec[51];
// 정점의 발견순서. 처음에는 -1로 초기화.
int visited[51];
//컴포넌트 번호.
int scc_id[51];
//정점의 번호를 담는 스택.
stack<int> st;
//인덱스.
int order = 0;
//컴포넌트 인덱스.
int scc_cnt = 0;
//컴포넌트 집합.
vector<vector<int>> com;
//이 도시에 경찰서 지었는지.
bool flag[51];
//SCC로 들어오는 간선의 수
int indegree[51];

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
    //아직 자식의 컴포넌트 번호가 배정된게 아니면.
    else if(scc_id[next]==-1)
      ret = min(ret, visited[next]);
  }
  // here에서 부모로 올라가는 간선을 끊어야 할 지 확인.
  if(ret == visited[here])
  {
    vector<int> new_scc;
    //here를 루트로 하는 서브트리에 정점들을 컴포넌트로 묶는다.
    while(true)
    {
      int t = st.top();
      st.pop();
      new_scc.push_back(t);
      scc_id[t] = scc_cnt;
      if(t == here)
        break;
    }
    scc_cnt++;
    com.push_back(new_scc);
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

  cin >> n;
  for(int i=1;i<=n;i++)
    cin >> cost[i];

  char c;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      cin >> c;
      //i에서j로가는 간선이 있으면.
      if(c=='Y')
        vec[i].push_back(j);
    }
  }

  for(int i=1;i<=n;i++)
  {
    if(visited[i] == -1)
      scc(i);
  }

  for(int i=1;i<=n;i++)
  {
    for(int j=0;j<vec[i].size();j++)
    {
      int next = vec[i][j];
      if(scc_id[i]!=scc_id[next])
        indegree[scc_id[next]]++;
    }
  }

  //경찰서 짓는 최소 비용.
  double min_cost = 0;
  //경찰서 지은 곳의 수.
  double cnt = 0;
  for(int i=0;i<com.size();i++)
  {
    //들어오는 간선이 있으면 일단 무시.
    if(indegree[i])
      continue;
    int min_val = 1234;
    //제일 건설 비용 작은 도시 인덱스.
    int min_id = -1; 
    //컴포넌트에서 경찰서 건설 비용이 제일 적은 도시 채택.
    for(int j=0;j<com[i].size();j++)
    {
      if(min_val>cost[com[i][j]])
      {
        min_val = cost[com[i][j]];
        min_id = com[i][j];
      }
    }
    flag[min_id] = true;
    min_cost += min_val;
    cnt++;
  }
  //채택되지 않은 도시들의 건설 비용 벡터.
  vector<int> rest;
  for(int i=1;i<=n;i++)
  {
    if(!flag[i])
      rest.push_back(cost[i]);
  }
 
  sort(rest.begin(),rest.end());

  //평균값을 낮추는 도시에도 경찰서 설치.
  for(int i=0;i<rest.size();i++)
  {
    if((min_cost/cnt) >= (min_cost+rest[i])/(cnt+1))
    {
      min_cost += rest[i];
      cnt++;
    }
  }
  
  cout << fixed;
  cout.precision(9);
  cout << min_cost/cnt;
  
  return 0;
}