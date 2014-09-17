#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const long long maxn = 1e18+100;
const int maxt = 1e7+100;
char t[maxt];
char x[maxt];
int nt;
long long n;
int trie[maxt][4], trie_n, trie_root;
long long dp[4][4];

void ins(int trie[][4], int root, char s[]) {
    int t = root;
    for ( ; *s; s++) {
        int c = (*s) - 'A';
        if (trie[t][c] == 0) {
            trie_n += 1;
			if (trie_n >= maxt) cout << 'shit' << endl;
            trie[t][c] = trie_n;
        }
        t = trie[t][c];
    }
}

bool qry(int trie[][4], int root, char s[]) {
    int t = root;
    for (; *s; s++) {
        int c = (*s) - 'A';
        if (trie[t][c] == 0)
            return false;
        t = trie[t][c];
    }
    return true;
}

void mul(long long a[4][4], long long b[4][4], long long c[4][4]) {
    long long t[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            t[i][j] = maxn;
            for (int k = 0; k < 4; k++)
                t[i][j] = min(t[i][j], a[i][k]+b[k][j]);
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            c[i][j] = t[i][j];
}

void cal(long long ret[4][4], long long a[4][4], long long k) {
    long long t[4][4];
	memcpy(t, a, sizeof(t));
	memcpy(ret, a, sizeof(t));
    for (k -= 1; k; k>>=1, mul(t, t, t))
        if (k & 1)
            mul(ret, t, ret);
}

bool check(long long a[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (a[i][j] < n)
                return true;
	return false;
}

void pre(long long ret[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j  = 0; j < 4; j++)
            ret[i][j] = maxn;
   
	int l = log(nt+1.0)/log(4.0) + 2;
    for (int i = 2; i <= l; i++)
        for (int j = 0; j < 1 << (2*i); j++) {
            int k, y;
            for (k = 0, y = j; k < i; k++, y >>= 2)
                x[k] = 'A' + (y & 3);
			x[i] = 0;
            if (qry(trie, trie_root, x) == false) {
                int l = x[0] - 'A';
				int r = x[i-1] - 'A';
				ret[l][r] = min(ret[l][r], (long long)i - 1);
			}
        }
}

long long gao() {
    long long a[4][4], ret[4][4];
    pre(a);
    long long l , r,  m;
    l = 1;
    r = n;
    while (l < r) {
        m = (l + r) >> 1;
        cal(ret, a, m);
        if(check(ret)) {
            l = m + 1;
        }else {
            r = m;
        }
    }
    return l;
}

int main() {
	//freopen("in.txt", "r", stdin);
    cin >> n >> t;
    trie_n = 1;
    trie_root = 1;
    nt = strlen(t);
    for (int i = 0; i < nt; i++) {
		int j;
		for (j = 0; i + j < nt && j < 30; j++) 
			x[j] = t[i+j];
		x[j] = 0;
        ins(trie, trie_root, x);
		//cout << i << ' ' << j << ' ' << trie_n << endl;
	}
    long long ans = gao();
    cout << ans << endl;
    return 0;
}