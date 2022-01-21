#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<memory.h>
#include<vector>
#include<cmath>
#include<stack>
#include<map>

using namespace std;

int n, m;
int sum = 0;

void cut(int len)
{
    // 더이상 못 자르면.
    if (m == 0 || len < 10)
        return;

    sum++;
    m--;
    len -= 10;

    if (len == 10)
        sum++;
    else if (len > 10)
        cut(len);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int num;
    //10으로 나눠지는 놈들.
    vector<int> v1;
    //10으로 안나눠지는 놈들.
    vector<int> v2;
    cin >> n >> m;
    while (n-- > 0)
    {
        cin >> num;
        if (num == 10)
            sum++;
        else if (num % 10 == 0)
            v1.push_back(num);
        else
            v2.push_back(num);
    }
    sort(v1.begin(), v1.end());
    
    for (int i = 0; i < v1.size(); i++)
        cut(v1[i]);

    for (int i = 0; i < v2.size(); i++)
        cut(v2[i]);

    cout << sum;

    return 0;
}