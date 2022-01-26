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

const int MAX_N = 2010;
int n, m;
// a -> b 가는 간선의 용량.
int capacity[MAX_N][MAX_N];
// a -> b 가는 간선의 유량.
int flow[MAX_N][MAX_N];
// a -> b 가는 간선의 비용.
int cost[MAX_N][MAX_N];
//그래프 인접리스트.
vector<int> vec[MAX_N];

//MCMF 알고리즘.
void MCMF(int source, int sink)
{
    //최소 비용.
    int min_cost = 0;
    //최대 유량.
    int totalFlow = 0;
    while (true)
    {
        //어느 정점에서 유량이 흘러왔는지 저장할 배열.
        int parent[MAX_N];
        //누적거리 저장할 배열.
        int dist[MAX_N];
        //해당 정점이 큐에 있는지.
        bool inQ[MAX_N];

        memset(parent, -1, sizeof(parent));
        fill(dist, dist + MAX_N, INF);
        memset(inQ, false, sizeof(inQ));

        //유량을 흘려보낼 정점을 저장할 큐.
        queue<int> q;

        dist[source] = 0;
        inQ[source] = true;
        q.push(source);

        //SPFA 알고리즘.
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            inQ[cur] = false;

            for (int i = 0; i < vec[cur].size(); i++)
            {
                int next = vec[cur][i];
                //최단 경로를 찾되 잔여 용량이 있어야함.
                if (capacity[cur][next] - flow[cur][next] > 0 && dist[next] > dist[cur] + cost[cur][next])
                {
                    dist[next] = dist[cur] + cost[cur][next];
                    parent[next] = cur;
                    if (!inQ[next])
                    {
                        q.push(next);
                        inQ[next] = true;
                    }
                }
            }
        }
        //증가 경로가 없으면 종료한다.
        if (parent[sink] == -1)
            break;
        //증가 경로를 통해서 얼마를 보낼지 결정.
        int amount = INF;
        //증가 경로의 간선 중에서 잔여 용량이 가장 작은 것을 유량으로 채택. 
        for (int cur = sink; cur != source; cur = parent[cur])
            amount = min(amount, capacity[parent[cur]][cur] - flow[parent[cur]][cur]);
        //증가 경로는 유량 증가, 역 방향 경로는 유량 감소.
        for (int cur = sink; cur != source; cur = parent[cur])
        {
            min_cost += amount * cost[parent[cur]][cur];
            flow[parent[cur]][cur] += amount;
            flow[cur][parent[cur]] -= amount;
        }
        totalFlow += amount;
    }
    cout << min_cost << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> n >> m)
    {
        memset(capacity, 0, sizeof(capacity));
        memset(flow, 0, sizeof(flow));
        memset(cost, 0, sizeof(cost));
        for (int i = 0; i <= 2009; i++)
            vec[i].clear();

        // 가중치 1인 in -> out 간선.
        for (int i = 2; i <= 2 * n; i += 2)
        {
            capacity[i][i + 1] = 1;
            vec[i].push_back(i + 1);
            vec[i + 1].push_back(i);
        }

        //정점 분할이 필요한 문제다.
        //인덱스는 2-SAT 느낌으로 in노드는 2n, out노드는 2n+1
        for (int i = 1; i <= m; i++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            //out -> in 의 역간선은 in -> out이다.
            vec[a * 2 + 1].push_back(b * 2);
            vec[b * 2].push_back(a * 2 + 1);

            cost[a * 2 + 1][b * 2] = w;
            cost[b * 2][a * 2 + 1] = -w;

            capacity[a * 2 + 1][b * 2] = 1;

        }

        // 시작점과 목적지는 겹쳐야 하므로 용량 2.
        capacity[1 * 2][1 * 2 + 1] = 2;
        capacity[n * 2][n * 2 + 1] = 2;

        MCMF(1 * 2, n * 2 + 1);
    }
    return 0;
}