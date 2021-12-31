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
vector<int> vec[100001];
// 정점의 발견순서. 처음에는 -1로 초기화.
int visited[100001];
//컴포넌트 번호.
int scc_id[100001];
//정점의 번호를 담는 스택.
stack<int> st;
//인덱스.
int order = 0;
//컴포넌트 인덱스.
int scc_cnt = 0;
//scc에 들어오는 간선의 수.
int indegree[100001];

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
    memset(indegree,0,sizeof(indegree));
    memset(scc_id,-1,sizeof(scc_id));
    for(int i=0;i<=100000;i++)
      vec[i].clear();
    scc_cnt = 0;
    order = 0;
    cin >> v >> e;
    for(int i=1;i<=e;i++)
    {
      int a,b;
      cin >> a >> b;
      vec[a].push_back(b);
    }
    for(int i=0;i<v;i++)
    {
      if(visited[i] == -1)
        scc(i);
    }

    for(int i=0;i<v;i++)
    {
      for(int j=0;j<vec[i].size();j++)
      {
        int next = vec[i][j];
        if(scc_id[i]!=scc_id[next])
          indegree[scc_id[next]]++;
      }
    }

    //indegree가 0인 SCC가 하나 존재해야 된다.
    //indegree가 0인 SCC가 2개 이상 존재하면
    //indegree가 0인 곳에서 다른 0인 곳으로 가지 못하므로 Confused. 
    vector<int> ans;
    int flag = -1;
    for(int i=0;i<v;i++)
    {
      if(!indegree[scc_id[i]])
      {
        //처음이거나 저번에 나온놈이랑 같은 컴포넌트라면.
        if(flag == -1 || flag == scc_id[i])
        {
          ans.push_back(i);
          flag = scc_id[i];
        }
        else
        {
          flag = -2;
          break;
        }
      }
    }
    if(flag == -2)
      cout << "Confused" <<"\n";
    else
    {
      for(int i=0;i<ans.size();i++)
        cout << ans[i] <<"\n";
    } 
    cout << "\n";
  }
  
  return 0;
}