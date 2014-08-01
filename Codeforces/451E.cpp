#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int n;
long long s, t, ret;
long long f[32];

const long long p = 1e9+7;

long long modexp(long long a, long long b, long long c) {
    long long ret = 1;
    for (a = a % c; b; a = a * a % c, b = b >> 1) 
	if (b & 1) 
	    ret = ret * a % c;
    return ret;
}

long long comb(long long n, long long m, long long c) {
    long long up = 1, down = 1;

    for (int i = 1; i <= m; i++) {
	up = up * (n - m + i) % c;
	down = down * i % c;
    }
    return up * modexp(down, c-2, c) % c;
}

long long lucas(long long n, long long m, long long c) {
    if (m == 0) return 1;
    return comb(n % c, m % c, c) * lucas(n / c, m / c, c) % c;
}


void input() {
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
	cin >> f[i];
    }
}

void solve() {
    ret = 0;
    for (int i = 0; i < (1<<n); i++) {
	int flag = 1;
	long long sum = s;
	for (int j = 0; j < n; j++) {
	    if ((i >> j) & 1) {
		flag = flag * -1;
		sum = sum - (f[j] + 1);
	    }
	}
	if (sum < 0) continue;
	ret = ret + flag * lucas(sum + n - 1, n - 1, p);
	ret = ret % p;
    }
}

void output(){
    cout << (ret + p) % p << endl;
}

int main() {
    input();
    solve();
    output();
    return 0;
}
