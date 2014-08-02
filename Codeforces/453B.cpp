#include <iostream>
#include <algorithm>

using namespace std;

const int g[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
int n, a[32], r[32];
int f[128][1<<10], c[128][1<<10];
vector<int> l[10]; 

void gao(int n, int mask) {
    if (mask == 0) return 0;
    int cc = c[n][mask];
    int m = 30, ccc;
    for (int i = 0; i < l[cc].size(); i++) {
	if (abs(l[cc][i] - r[cc]) < m) {
	    r[cc] = l[n][i];
	}
    }
    gao(n-1, mask ^ (1<<cc));
}

int main() {
    for (int i = 0; i < 10; i++) {
	for (int j = 1; j * g[i] <= 30; j++)
	    l[i].push_back(j * g[i]);
    }

    cin >> n;
    for (int i = 1; i <= n; i++)  {
	cin >> a[i];
	r[i] = a[i];
    }

    for (int i = 1; i <= n; i++) {
	f[i][0] = f[i-1][0] + abs(a[i]-1);
	for (int j = 1; j < (1<<10); j++) {
	    int m = f[i][0], cc;
	    for (int k = 0; k < 10; k++) 
		if (j >> k & 1) {
		    int mm = 30;
		    for (int t = 0; t < l[k].size(); t++)
			mm = min(mm, abs(a[i]-l[k][t]));		
		    if (m > f[i-1][j ^ (1 << k)]) {
			m = f[i-1][j ^ (1 << k)];
			cc = k;
		    }	
		}
	    f[i][j] = m;
	    c[i][j] = cc;
	}
     }

    int m = 30*n, cc;
    for (int i = 0; i < (1<<10); i++) 
	if (m > f[n][i]) {
	    m = f[n][i];
	    cc = i;
	}
  
    gao(n, i);
    for (int i = 1; i <= n; i++) {
	cout << r[i];
	if (i != n) cout << ' ';
	else cout << endl;
    }
    return 0;
}
