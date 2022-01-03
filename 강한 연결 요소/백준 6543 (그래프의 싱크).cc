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
//scc에서 나가는 간선의 수.
int outdegree[100001];

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

  while(true)
  {
    memset(visited,-1,sizeof(visited));
    memset(outdegree,0,sizeof(outdegree));
    memset(scc_id,-1,sizeof(scc_id));
    for(int i=0;i<=100000;i++)
      vec[i].clear();
    order = 0;
    scc_cnt = 0;

    cin >> v;
    if(v == 0)
      break;
    cin >> e;

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
    //자신으로부터 도달할 수 있는 모든 노드로부터 돌아오는 경로가 존재하려면
    //자신이 속한 Component에서 다른 Component로 가는 간선이 없어야함.
    for(int i=1;i<=v;i++)
    {
      for(int j=0;j<vec[i].size();j++)
      {
        int next = vec[i][j];
        if(scc_id[i]!=scc_id[next])
          outdegree[scc_id[i]]++;
      }
    }

    vector<int> ans;
    for(int i=1;i<=v;i++)
    {
      if(!outdegree[scc_id[i]])
      {
        ans.push_back(i);
      }
    }
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++)
      cout << ans[i] << " ";
    cout << "\n";
  }
  
  return 0;
}