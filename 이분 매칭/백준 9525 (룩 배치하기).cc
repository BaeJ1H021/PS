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

//테이프가 10000개는 못넘는다.
const int MAX = 10001;

// A와 B의 정점의 개수
int n;
// adj[i] : A[i]와 인접한 그룹 B의 정점들.
vector<int> adj[MAX];
// A[i], B[i] : 각 정점에 매칭된 반대편 정점 번호.
int A[MAX], B[MAX];
// dfs의 방문 여부.
bool visited[MAX];
// 게시판 배열
char arr[101][101];
// 행번호와 열번호 담은 배열.
int r[101][101];
int c[101][101];
// 테이프 아이디.
int row_id = 1;
int col_id = 1;

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

    for (int i = 1; i < row_id; i++)
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

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> arr[i][j];
        }
    }

    // 가로로 놓는 룩.
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (arr[i][j] == '.')
            {
                while (j <= n && arr[i][j] == '.')
                {
                    r[i][j] = row_id;
                    j++;
                }
                row_id++;
            }
        }
    }
    // 세로로 놓는 룩.
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (arr[j][i] == '.')
            {
                while (j <= n && arr[j][i] == '.')
                {
                    c[j][i] = col_id;
                    j++;
                }
                col_id++;
            }
        }
    }

    // 최소 버텍스 커버의 크기 = 이분매칭의 최대크기
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (arr[i][j] == '.')
                adj[r[i][j]].push_back(c[i][j]);
        }
    }

    cout << bipartiteMatch();

    return 0;
}