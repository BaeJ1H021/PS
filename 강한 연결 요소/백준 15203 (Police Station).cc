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

//10^6이 100000이 아니라 억까당한 문제.
//아무튼 억까임.
int v,e;
//그래프의 인접리스트 표현.
vector<int> vec[1000001];
// 정점의 발견순서. 처음에는 -1로 초기화.
int visited[1000001];
//컴포넌트 번호.
int scc_id[1000001];
//정점의 번호를 담는 스택.
stack<int> st;
//인덱스.
int order = 0;
//컴포넌트 인덱스.
int scc_cnt = 0;
//scc에 들어오는 간선의 수.
int indegree[1000001];

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

  memset(visited,-1,sizeof(visited));
  memset(scc_id,-1,sizeof(scc_id));
  
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
        indegree[scc_id[next]]++;
    }
  }

  //indegree가 0인 SCC가 하나 존재해야 된다.
  //indegree가 0인 SCC가 2개 이상 존재하면
  //indegree가 0인 곳에서 다른 0인 곳으로 가지 못하므로 0.
  vector<int> ans;
  int flag = -1;
  for(int i=1;i<=v;i++)
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
  {
    cout << 0 <<"\n";
  }
  else
  {
    sort(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(int i=0;i<ans.size();i++)
      cout << ans[i] <<" ";
  } 
  
  return 0;
}