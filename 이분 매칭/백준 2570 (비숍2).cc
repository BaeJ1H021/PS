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

//비숍 아이디가 10000은 못넘는다.
const int MAX = 10001;

int n, m;
// adj[i] : A[i]와 인접한 그룹 B의 정점들.
vector<int> adj[MAX];
// A[i], B[i] : 각 정점에 매칭된 반대편 정점 번호.
int A[MAX], B[MAX];
// dfs의 방문 여부.
bool visited[MAX];
// 체스판 배열.
bool obs[105][105];
// 행번호와 열번호 담은 배열.
int l[105][105];
int r[105][105];
// 대각선 아이디.
int left_id = 1;
int right_id = 1;

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

    for (int i = 1; i <= left_id; i++)
    {
        memset(visited, false, sizeof(visited));
        if (dfs(i))
            cnt++;
    }
    return cnt;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    cin >> m;

    // 장애물 설정.
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        obs[a][b] = true;
    }

    // 왼쪽 대각선으로 놓는 비숍.
    for (int k = -(n - 1); k <= (n - 1); k++)
    {
        int i, j;
        if (k > 0)
            i = k + 1, j = 1;
        else
            i = 1, j = 1 - k;

        while (i <= n && j <= n)
        {
            if (!obs[i][j])
            {
                l[i][j] = left_id;
                if (i == n || j == n || (i < n && j < n && obs[i + 1][j + 1]))
                    left_id++;
            }
            i++, j++;
        }
    }

    // 오른쪽 대각선으로 놓는 비숍.
    for (int k = 2; k <= 2 * n; k++)
    {
        int i, j;
        if (k <= 1 + n)
            i = k - 1, j = 1;
        else
            i = n, j = k - n;

        while (i >= 1 && j <= n)
        {
            if (!obs[i][j])
            {
                r[i][j] = right_id;
                if (i == 1 || j == n || (i > 1 && j < n && obs[i - 1][j + 1]))
                    right_id++;
            }
            i--, j++;
        }
    }

    // 최소 버텍스 커버의 크기 = 이분매칭의 최대크기
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (!obs[i][j])
                adj[l[i][j]].push_back(r[i][j]);
        }
    }

    cout << bipartiteMatch();

    return 0;
}