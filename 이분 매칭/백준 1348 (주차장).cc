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

// 차의 개수가 100을 못넘는다.
const int MAX = 101;

int n, m;
// adj[i] : A[i]와 인접한 그룹 B의 정점들.
vector<int> adj[MAX];
// A[i], B[i] : 각 정점에 매칭된 반대편 정점 번호.
int A[MAX], B[MAX];
// dfs의 방문 여부.
bool visited[MAX];
// 주차장 배열.
char arr[55][55];
// 차량 번호 배열.
int car_num[55][55];
// 주차장 번호 배열.
int park_num[55][55];
// 차와 주차장의 개수.
int car_cnt = 0;
int park_cnt = 0;
// 차와 주차장의 최단거리.
int dist[101][101];

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

void bfs(int y,int x)
{
    // 내 차의 번호.
    int mine = car_num[y][x];
    bool visit[55][55];
    memset(visit, false, sizeof(visit));
    visit[y][x] = true;
    queue<pair<int,int>> q;
    q.push({ y, x });

    int cnt = 1;

    while (!q.empty())
    {
        int q_size = q.size();
        while (q_size-- > 0)
        {
            int cur_y = q.front().first;
            int cur_x = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int ny = cur_y + dy[i];
                int nx = cur_x + dx[i];
                if (nx < 1 || nx > m || ny <1 || ny>n)
                    continue;
                if (!visit[ny][nx])
                {
                    if (arr[ny][nx] == 'C' || arr[ny][nx] == '.')
                    {
                        visit[ny][nx] = true;
                        q.push({ny,nx});
                    }
                    else if (arr[ny][nx] == 'P')
                    {
                        visit[ny][nx] = true;
                        q.push({ ny, nx });
                        dist[mine][park_num[ny][nx]] = cnt;
                        adj[mine].push_back(park_num[ny][nx]);
                    }
                }
            }
        }
        cnt++;
    }
}

// A 그룹의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로 탐색. 
bool dfs(int a,int time)
{
    if (visited[a])
        return false;
    visited[a] = true;
    for (int i = 0; i < adj[a].size(); i++)
    {
        int b = adj[a][i];
        // 여유시간안에 도착할 수 없는 거리면 무시.
        if (dist[a][b] > time)
            continue;
        // 반대편이 매칭되지 않았거나
        // 매칭되어 있었지만 원래 매칭되어 있던 정점을 다른 정점과 매칭가능하다면.
        if (B[b] == -1 || dfs(B[b],time))
        {
            A[a] = b;
            B[b] = a;
            return true;
        }
    }
    return false;
}

int bipartiteMatch(int limit)
{
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    // 매칭의 수.
    int cnt = 0;

    for (int i = 1; i <= car_cnt; i++)
    {
        memset(visited, false, sizeof(visited));
        if (dfs(i,limit))
            cnt++;
    }
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'C')
            {
                car_num[i][j] = ++car_cnt;
            }
            else if (arr[i][j] == 'P')
            {
                park_num[i][j] = ++park_cnt;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (arr[i][j] == 'C')
                bfs(i, j);
        }
    }

    // 이분탐색으로 최소 시간을 낮춰준다.
    int left = 0;
    int right = 2500;
    // 주차 불가능하다면 -1 출력.
    int ans = -1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        //모든 차들이 매칭되면.
        if (bipartiteMatch(mid) == car_cnt)
        {
            right = mid - 1;
            ans = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    cout << ans;
  
    return 0;
}