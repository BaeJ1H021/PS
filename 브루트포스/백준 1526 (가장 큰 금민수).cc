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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = n; i >= 4; i--)
    {
        int num = i;
        bool flag = true;
        while (num > 0)
        {
            if (num % 10 != 4 && num % 10 != 7)
            {
                flag = false;
                break;
            }
            num /= 10;
        }
        if (flag)
        {
            cout << i;
            break;
        }
    }

    return 0;
}