#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int N, K;
const int maxn = 1e6;
const long long mod = 1e9+7;
int p[maxn];

int getp(int x)
{
    if (x == p[x]) return x;
    else return p[x] = getp(p[x]);
}

void uni(int x, int y)
{
    int px = getp(x);
    int py = getp(y);
    p[px] = py;
}

bool qry(int x, int y)
{
    int px = getp(x);
    int py = getp(y);
    return px == py;
}

void gao(int i, int j, string s)
{
    int l, r;
    if (i + j <= N + 1)
    {
        r = i + j - 1;
    }
    else
    {
        r = 2 * N - i - j + 1;
    }
    l = abs(i - j) + 1;
   // cout << l << ' ' << r <<endl;
    if (s[0] == 'o')
    {
        //cout << s <<endl;
        uni(2*(l-1), 2*(r+1)+1);
        uni(2*(l-1)+1, 2*(r+1));
    }
    else
    {
        //cout << s << endl;
        uni(2*(l-1), 2*(r+1));
        uni(2*(l-1)+1, 2*(r+1)+1);
    }
}

int main()
{
    cin >> N >> K;
    for (int i = 0; i <= N + 1; i++) {
            p[i*2] = i*2;
            p[i*2+1] = i*2+1;
    }
    while (K--)
    {
        int a, b;
        string s;
        cin >> a >> b >> s;
        gao(a, b, s);
    }
    bool flag = true;
    int cnt = 0;
    for (int i = 0; i <= N + 1; i++)
    {
       // cout <<i <<endl;
        if (qry(i*2, i*2+1) == true)
        {
            flag = false;
        }
        if (getp(i*2) == i*2) cnt++;
        if (getp(i*2+1) == i*2+1) cnt++;
    }
//    for (int i = 0; i <= N; i++) {
//        cout << i << ' ' << getp(i*2) << ' ' << getp(i*2+1)<< endl;
//    }
    if (flag == false)
    {
        cout << 0 <<endl;
    }
    else
    {
        long long ans = 1;
        cnt = cnt / 2 - 2;
        for (int i = 1; i <= cnt; i++)
            ans = ans * 2 % mod;
        cout << ans <<endl;
    }
    return 0;
}
