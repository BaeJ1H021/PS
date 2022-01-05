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
//그래프의 인접리스트 표현.
vector<int> vec[20001];
// 정점의 발견순서. 처음에는 -1로 초기화.
int visited[20001];
//컴포넌트 번호.
int scc_id[20001];
//정점의 번호를 담는 스택.
stack<int> st;
//인덱스.
int order = 0;
//컴포넌트 인덱스.
int scc_cnt = 0;
//scc에 들어오는 간선의 수.
int indegree[20001];
//scc에서 나가는 간선의 수.
int outdegree[20001];

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

  int T;
  cin >> T;
  while(T-->0)
  {
    memset(visited,-1,sizeof(visited));
    memset(scc_id,-1,sizeof(scc_id));
    memset(indegree,0,sizeof(indegree));
    memset(outdegree,0,sizeof(outdegree));
    scc_cnt = 0;
    order = 0;
    for(int i=0;i<=20000;i++)
      vec[i].clear();

    cin >> v >> e;
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
          indegree[scc_id[next]]++;
          outdegree[scc_id[i]]++;
        }
      }
    }

    //outdegree가 0인 컴포넌트를 indegree가 0인 컴포넌트에 연결.
    //indegree가 0인 컴포넌트를 outdegree가 0인 컴포넌트에 연결.
    int in_zero = 0;
    int out_zero = 0;
    for(int i=0;i<scc_cnt;i++)
    { 
      if(!indegree[i])
        in_zero++;
      if(!outdegree[i])
        out_zero++;
    }
    //SCC가 1개라면 indegree,outdegree 모두 0이지만 이미 동치 증명.
    if(scc_cnt == 1)
      cout << 0 << "\n";
    else
      cout << max(in_zero,out_zero) << "\n";
  }  
  return 0;
}