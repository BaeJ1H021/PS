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
            //전체 비용이 각 간선 비용 * 유량만큼 증가.
            min_cost += amount * cost[parent[cur]][cur];
            flow[parent[cur]][cur] += amount;
            flow[cur][parent[cur]] -= amount;
        }
        totalFlow += amount;
    }
    cout << min_cost;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 양방향 간선이므로 cost[i][j] = -cost[j][i] 로 설정할 수 없다. 
    // 따라서 구조체를 선언하거나, 정점 분할을 통해서 in, out노드를 만들어주면 된다.
    // 나라 : 2~2001, in : 2n , out : 2n+1.
    cin >> n >> m;
    
    //1번 나라에서 N번 나라로 왕복하는 비용은 
    //1번에서 N번으로 가는 최소 비용 + 1번에서 N번으로 가는 두번째 최소 비용(경로 안 겹치는)
    
    // in -> out 간선은 가중치가 2.
    for (int i = 2; i <= 2 * n; i += 2)
    {
        capacity[i][i + 1] = 2;
        vec[i].push_back(i + 1);
        vec[i+1].push_back(i);
    }

    for (int i = 1; i <= m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;

        vec[a * 2 + 1].push_back(b * 2); // a -> b out -> in
        vec[b * 2].push_back(a * 2 + 1); // a -> b 역방향 간선.
        vec[b * 2 + 1].push_back(a * 2); // b -> a out -> in
        vec[a * 2].push_back(b * 2 + 1); // b -> a 역방향 간선.

        // 용량은 out -> in 간선에만 1 주어진다.
        capacity[a*2+1][b*2] = 1;
        capacity[b*2+1][a*2] = 1;

        cost[a * 2 + 1][b * 2] = w;
        cost[b * 2][a * 2 + 1] = -w;

        cost[b * 2 + 1][a * 2] = w;
        cost[a * 2][b * 2 + 1] = -w;
    }

    MCMF(2, 2 * n + 1);

    return 0;
}