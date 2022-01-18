#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>
#include<stack>
#include<map>

#define INF 2e9

using namespace std;

const int MAX_N = 802;
int n,m;
// a -> b 가는 간선의 용량.
int capacity[MAX_N][MAX_N];
// a -> b 가는 간선의 유량.
int flow[MAX_N][MAX_N];

//에드몬드-카프 알고리즘.
int networkFlow(int source, int sink)
{
  int totalFlow = 0;
  while(true)
  {
    //어느 정점에서 유량이 흘러왔는지 저장할 배열.
    int parent[MAX_N];
    memset(parent,-1,sizeof(parent));

    //유량을 흘려보낼 정점을 저장할 큐.
    queue<int> q;

    parent[source] = source;
    q.push(source);

    while(!q.empty() && parent[sink] == -1)
    {
      int cur = q.front();
      q.pop();

      for(int next=0;next<MAX_N;next++)
      {
        //잔여용량이 남아있고 아직 방문하지 않았다면.
        if(capacity[cur][next]-flow[cur][next] > 0  && parent[next]==-1)
        {
          q.push(next);
          parent[next] = cur;
        }
      }
    }
    //증가 경로가 없으면 종료한다.
    if(parent[sink]==-1)
      break;
    //증가 경로를 통해서 얼마를 보낼지 결정.
    int amount = INF;
    //증가 경로의 간선 중에서 잔여 용량이 가장 작은 것을 유량으로 채택. 
    for(int cur = sink;cur!=source;cur=parent[cur])
      amount = min(amount,capacity[parent[cur]][cur]-flow[parent[cur]][cur]);
    //증가 경로는 유량 증가, 역 방향 경로는 유량 감소.
    for(int cur = sink;cur!=source;cur=parent[cur])
    {
      flow[parent[cur]][cur] += amount;
      flow[cur][parent[cur]] -= amount;
    }
    totalFlow += amount;
  }
  return totalFlow;
}

int main()                             
{ 
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);


  cin >> n >> m;

  // 가중치 1인 in -> out 간선.
  for(int i=2;i<=2*n;i+=2)
    capacity[i][i+1] = 1;

  while(m-->0)
  {
    int a,b;
    cin >> a >> b;
    
    //정점 분할이 필요한 문제다.
    //인덱스는 2-SAT 느낌으로 in노드는 2n, out노드는 2n+1
    capacity[a*2+1][b*2] = 1;
    capacity[b*2+1][a*2] = 1;
  }

  // 1번의 out노드 -> 2번의 in노드
  cout << networkFlow(1*2+1,2*2);
  return 0;
}