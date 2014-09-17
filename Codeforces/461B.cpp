#include <iostream>
#include <algorithm>

using namespace std;

const long long P = 1e9+7;
const int N = 1e5 + 10;
long long n;
long long w[N], b[N], c[N];
vector<long long> e[N];

long long modexp(long long a, long long b, long long c) {
    long long ret = 1;
    for (a = a % c; b; b >>= 1, a = a * a % c) 
	if (b & 1) 
	    ret = ret * a % c;
    return ret;
}

void gao(long long x, long long pa = -1) {
    if (e[x].size() == 0)  {
        if (c[x] == 1) {
	    b[x] = 1;
	    w[x] = 0;
        }else {
	    b[x] = 0;
	    w[x] = 1;
        }
	return;
    }

    long long s = 1;
    for (int i = 0; i < e[x].size(); i++)
	if (e[x][i] != pa) {
	    gao(e[x][i], x);
	    s = s * (b[e[x][i]]+w[e[x][i]]) % P;
	}

    if (c[x] == 1) {
	w[x] = 0;
	b[x] = s;
    }else {
	w[x] = s;
	b[x] = 0;
	for (int i = 0; i < e[x].size(); i++) 
	    if (e[x][i] != pa) {
		b[x] = (b[x] + (b[e[x][i]] * s % P
			      * modexp((b[e[x][i]]+w[e[x][i]]),P-2,P))
		       )%P;
	}
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
	int t;
	cin >> t;
	e[t].push_back(i);
	e[i].push_back(t);
    }

    for (int i = 0; i < n; i++)
	cin >> c[i];
    gao(0);
    for (int i = 0; i < n; i++) {
//	cout << i << ": " <<  b[i] << ' ' << w[i] << endl;
    }
    cout << b[0] % P << endl;
    return 0;
}


