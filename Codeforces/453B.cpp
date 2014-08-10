#include <iostream>
#include <algorithm>

using namespace std;

int n, maxf;
const int nl = 17;
const int maxn = 128;
const int trange = 59;
const int l[nl] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 
                  41, 43, 47, 53, 59};
int a[maxn], mt[trange+1];
int f[maxn][1<<nl], c[maxn][1<<nl], p[maxn][1<<nl];
int ans[maxn];

int main() {
   for (int i = 1; i <= 59; i++) {
	for (int j = 0; j < nl; j++) {
	    if (i % l[j] == 0) {
		mt[i] |= 1 << j;
	    }
	}
   }

   cin >> n;
   for (int i = 0; i < n; i++) 
       cin >> a[i];

   maxf = 30 * n;
   for (int i = 0; i <= n; i++)
       for (int j = 0; j < 1<<nl; j++)
	   f[i][j] = maxf;

   f[0][0] = 0;
   for (int i = 0; i < n; i++)
       for (int j = 0; j < 1<<nl; j++)
	   for (int k = 1; k <= trange; k++){
	       if (f[i][j] != maxf && ((j & mt[k]) == 0)) {
		   int tm = j | mt[k];
		   if (f[i+1][tm] > f[i][j] + abs(a[i]-k)) {
		       c[i+1][tm] = k;
		       p[i+1][tm] = j;
		       f[i+1][tm] = f[i][j] + abs(a[i]-k);
		   }
	       }
	   }

   int r, mm = maxf;
   for (int i = 0; i < 1<<nl; i++) {
       if (f[n][i] < mm) {
	   mm = f[n][i];
	   r = i;
       }
   }

   for (int i = n; i >= 1; i--) {
       ans[i] = c[i][r];
       r = p[i][r];
   }

   for (int i = 1; i <= n; i++) {
       cout << ans[i];
       if (i == n) cout << endl;
       else cout << ' ';
   }
   return 0;
}
