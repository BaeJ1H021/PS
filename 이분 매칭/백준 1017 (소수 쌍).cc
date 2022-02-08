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

const int MAX = 51;

// A와 B의 정점의 개수
int n;
// adj[i] : A[i]와 인접한 그룹 B의 정점들.
vector<int> adj[MAX];
// A[i], B[i] : 각 정점에 매칭된 반대편 정점 번호.
int A[MAX], B[MAX];
// dfs의 방문 여부.
bool visited[MAX];
//입력받는 배열.
int arr[51];
//홀수 벡터.
vector<int> v1;
//짝수 벡터.
vector<int> v2;
// 소수인지 판독.
bool flag[2001];
// 정답 벡터.
vector<int> ans;

// A 그룹의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로 탐색. 
bool dfs(int a)
{
    // a가 첫번째 수면 이미 다른 놈과 매칭. 건드리면 안됨.
    if ( a==0 || visited[a])
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

// 처음꺼를 하나씩 매칭시켜놓는다.
void one_by_one()
{
    for (int i = 0; i < adj[0].size(); i++)
    {
        memset(A, -1, sizeof(A));
        memset(B, -1, sizeof(B));
        int b = adj[0][i];
        // 하나 이미 연결.
        int cnt = 1;
        A[0] = b;
        B[b] = 0;
        for (int i = 1; i < v1.size(); i++)
        {
            memset(visited, false, sizeof(visited));
            if (dfs(i))
                cnt++;
        }
        if (cnt == n / 2)
            ans.push_back(v2[b]);
    }
    if (ans.size() == 0)
        cout << -1;
    else
    {
        sort(ans.begin(), ans.end());
        for (auto num : ans)
            cout << num << " ";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 에라토스테네스의 체.
    memset(flag, true, sizeof(flag));
    flag[0] = flag[1] = false; //0과 1은 소수가 아님.
    for (int i = 2; i <= sqrt(2000); i++)
    {
        if (flag[i]) //소수면
            for (int j = 2 * i; j <= 2000; j += i) //배수 X처리.
                flag[j] = false;
    }
    
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        if (arr[i] % 2 == 1)
            v1.push_back(arr[i]);
        else
            v2.push_back(arr[i]);
    }
    
    // 맨 첫번째 놈이 짝수면 swap.
    if (arr[1] % 2 == 0)
    {
        swap(v1, v2);
    }

    // 홀수와 짝수의 합이 소수면.
    for (int i = 0; i < v1.size(); i++)
    {
        for (int j = 0; j < v2.size(); j++)
        {
            if (flag[v1[i] + v2[j]])
            {
                adj[i].push_back(j);
            }
        }
    }
    
    one_by_one();

    return 0;
}