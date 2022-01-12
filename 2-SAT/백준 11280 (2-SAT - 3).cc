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
vector<int> vec[20010];
// 정점의 발견순서. 처음에는 -1로 초기화.
int visited[20010];
//컴포넌트 번호.
int scc_id[20010];
//정점의 번호를 담는 스택.
stack<int> st;
//인덱스.
int order = 0;
//컴포넌트 인덱스.
int scc_cnt = 0;

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
  
    if(a>0)
      a = a * 2;
    else
      a = (-a) * 2 + 1;

    if(b>0)
      b = b * 2;
    else
      b = (-b) * 2 + 1;

    //1과의 xor 연산을 통해서 a -> not_a 로 바꿔준다.
    vec[a^1].push_back(b);
    vec[b^1].push_back(a);
  }
  
  for(int i=2;i<=2*v+1;i++)
  {
    if(visited[i] == -1)
      scc(i);
  }

  bool flag = true;
  for(int i=2;i<=2*v;i+=2)
  {
    //A와 not A가 같은 컴포넌트에 있는 경우.
    if(scc_id[i] == scc_id[i+1])
    {
      flag = false;
      break;
    }
  }

  if(flag)
    cout << 1;
  else
    cout << 0;

  return 0;
}