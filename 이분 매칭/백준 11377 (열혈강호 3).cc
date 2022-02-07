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

const int MAX = 1001;

// A와 B의 정점의 개수
int n, m, k;
// adj[i] : A[i]와 인접한 그룹 B의 정점들.
vector<int> adj[MAX];
// A[i], B[i] : 각 정점에 매칭된 반대편 정점 번호.
int A[MAX], B[MAX];
// dfs의 방문 여부.
bool visited[MAX];

// A 그룹의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로 탐색. 
bool dfs(int a)
{
    if (visited[a])
        return false;
    visited[a] = true;
    for (int i = 0; i < adj[a].size(); i++)
    {
        int b = adj[a][i];
        // 반대편이 매칭되지 않았거나
        // 매칭되어 있었지만 원래 매칭되어 있던 정점을 다른 정점과 매칭가능하다면.
        if (B[b] == -1 || dfs(B[b]))
        {
            A[a] = b;
            B[b] = a;
            return true;
        }
    }
    return false;
}

int bipartiteMatch()
{
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    // 매칭의 수.
    int cnt = 0;

    for (int i = 1; i <= n; i++)
    {
        memset(visited, false, sizeof(visited));
        if (dfs(i))
            cnt++;
    }
    // k명은 일을 2개 시킨다.
    for (int i = 1; i <= n; i++)
    {
        memset(visited, false, sizeof(visited));
        if (k == 0)
            break;
        if (dfs(i))
        {
            cnt++;
            k--;
        }
    }
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        int num, task;
        cin >> num;
        while (num-- > 0)
        {
            cin >> task;
            adj[i].push_back(task);
        }
    }

    cout << bipartiteMatch();

    return 0;
}