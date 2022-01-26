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

//시작점.
const int from = 0;
//끝점.
const int to = 201;
const int MAX_N = 210;
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

    cin >> n;

    // 시작점 : 0, 학생 : 1~100, 문제 : 101~200, 끝점 : 201. 

    //시작점과 학생들을 연결.
    for (int i = 1; i <= n; i++)
    {
        capacity[from][i] = 1;
        vec[from].push_back(i);
        vec[i].push_back(from);
    }

    //끝점과 문제들을 연결.
    for (int i = 1; i <= n; i++)
    {
        capacity[i + 100][to] = 1;
        vec[i + 100].push_back(to);
        vec[to].push_back(i + 100);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int num;
            cin >> num;

            vec[i].push_back(j+100);
            vec[j+100].push_back(i);

            cost[i][j + 100] = num;
            cost[j + 100][i] = -num;

            //한 학생은 학 문제만 풀거임.
            capacity[i][j + 100] = 1;
        }
    }

    MCMF(from, to);

    return 0;
}