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

const int MAX = 7510;

// A와 B의 정점의 개수
int n;
// adj[i] : A[i]와 인접한 그룹 B의 정점들.
vector<long long> adj[MAX];
// A[i], B[i] : 각 정점에 매칭된 반대편 정점 번호.
int A[MAX], B[MAX];
// dfs의 방문 여부.
bool visited[MAX];
// 입력 받는 배열.
long long arr[MAX][2];
// 수들 저장하는 벡터.
vector<long long> v;

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
        cin >> arr[i][0] >> arr[i][1];
        
        v.push_back(arr[i][0] + arr[i][1]);
        v.push_back(arr[i][0] - arr[i][1]);
        v.push_back(arr[i][0] * arr[i][1]);
    }

    sort(v.begin(),v.end());
    //중복 제거.
    v.erase(unique(v.begin(), v.end()), v.end());

    for (int i = 1; i <= n; i++)
    {
        for (long long x : {
            arr[i][0] + arr[i][1],
            arr[i][0] - arr[i][1],
            arr[i][0] * arr[i][1]
        }) 
        {
            auto id = lower_bound(v.begin(), v.end(), x) - v.begin();
            adj[i].push_back(id);
        }
    }

    if (bipartiteMatch() != n)
        cout << "impossible";
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (v[A[i]] == arr[i][0] + arr[i][1])
                cout << arr[i][0] << " + " << arr[i][1] << " = " << v[A[i]] << "\n";
            else if (v[A[i]] == arr[i][0] - arr[i][1])
                cout << arr[i][0] << " - " << arr[i][1] << " = " << v[A[i]] << "\n";
            else if (v[A[i]] == arr[i][0] * arr[i][1])
                cout << arr[i][0] << " * " << arr[i][1] << " = " << v[A[i]] << "\n";
        }
    }
    return 0;
}