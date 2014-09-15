#include <iostream>
#include <algorithm>

using namespace std;

int N, Q;
const int maxn = 1e6;
int s[maxn];

void ins(int a[], int x, int t)
{
    for (; x < maxn; x += (x & (-x)) )
        a[x] += t;
}

int sum(int a[], int x)
{
    int ret = 0;
    for (; x; x -= (x & (-x)) )
        ret += a[x];
    return ret;
}

void update(int i, int j)
{
    int t = sum(s, i) - sum(s, i - 1);
    ins(s, j, t);
    ins(s, i, -t);
}

int main()
{
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        ins(s, i, 1);
    char head = 'l';
    int l = 1, r = N;
    while (Q--)
    {
        int type, x, a, b;
        int n = r - l + 1;
        cin >> type;
        if (type == 1)
        {
            cin >> x;
            if (head == 'l')
            {
                if (x <= n / 2)
                {
                    for (int i = l + x - 1, j = l + x; i >= l; i--, j++)
                    {
                        update(i, j);
                    }
                    l = l + x;
                }
                else
                {
                    for (int i = l + x, j = l + x - 1; i <= r; i++, j--)
                    {
                        update(i, j);
                    }
                    r = l + x - 1;
                    head = 'r';
                }
            }
            else
            {
                if (x <= n / 2)
                {
                    for (int i = r - x + 1, j = r - x; i <= r; i++, j--)
                    {
                        update(i, j);
                    }
                    r = r - x;
                }
                else
                {
                    for (int i = r - x, j = r - x + 1; i >= l; i--, j++)
                    {
                        update(i, j);
                    }
                    l = r - x + 1;
                    head = 'l';
                }
            }
//            for (int i = l; i <= r; i++)
//            {
//                cout << i << ": " << sum(s, i) - sum(s, i-1) <<endl;
//            }
//            cout <<endl;
        }
        else
        {
            cin >> a >> b;
            if (head == 'l')
            {
                cout << sum(s, l + b - 1) - sum(s, l + a - 1) << endl;
            }
            else
            {
                cout << sum(s, r  - a) - sum(s, r - b) << endl;
            }
        }
    }
    return 0;
}
