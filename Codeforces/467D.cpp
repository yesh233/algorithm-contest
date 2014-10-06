#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

const int maxn = 1e6;
vector<string> str_m;
map<string, int> d;
int d_n;
int cnt_r[maxn], cnt_len[maxn];
int c_r[maxn], c_len[maxn];
vector<int> e[maxn], c_e[maxn];
int low[maxn], num[maxn], c[maxn];
bool vis[maxn], instack[maxn];
stack<int> st;
int m, n, num_n, c_n;

int setid(string s) {
	transform(s.begin(), s.end(), s.begin(), tolower);
	str_m.push_back(s);
	if (d.find(s) == d.end()) {
		d_n += 1;
		d[s] = d_n;
	}
	int x = d[s];
	cnt_r[x] = count(s.begin(), s.end(), 'r');
	cnt_len[x] = s.length();
	return x;
}

void update(int x, int y, int *r, int *len) {
	if (r[y] < r[x] ||
		r[y] == r[x] && len[y] < len[x]) {
		r[x] = r[y];
		len[x] = len[y];
	}
}

void comp(int x) {
	c_n += 1;
	int y;
	do{
		y = st.top();
		instack[y] = false;
		c[y] = c_n;
		update(x, y, cnt_r, cnt_len);
		st.pop();
	} while (x != y);
	c_r[c_n] = cnt_r[x];
	c_len[c_n] = cnt_len[x];
}

void tarjan(int x, int p) {
	num_n += 1;
	num[x] = num_n;
	low[x] = num_n; 
	st.push(x);
	instack[x] = true;
	for (int i = 0; i < e[x].size(); i++) {
		if (num[e[x][i]] == 0) {
			tarjan(e[x][i], x);
			low[x] = min(low[x], low[e[x][i]]);
		}
		else if (instack[e[x][i]] == true){
			low[x] = min(low[x], num[e[x][i]]);
		}
	}
	if (num[x] == low[x]) {
		comp(x);
	}
}

void gao(int x) {
	vis[x] = true;
	for (int i = 0; i < c_e[x].size(); i++) {
			if (vis[c_e[x][i]] == false) {
				gao(c_e[x][i]);
			}
			update(x, c_e[x][i], c_r, c_len);
	}
}

int main() {
	cin >> m;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		setid(s);
	}

	cin >> n;
	for (int i = 0; i < n; i++) {
		string s, t;
		cin >> s >> t;
		int sid, tid;
		sid = setid(s);
		tid = setid(t);
		e[sid].push_back(tid);
	}

	for (int i = 1; i <= d_n; i++) 
		if (num[i] == 0) {
			tarjan(i, -1);
		}

	for (int i = 1; i <= d_n; i++) {
		for (int j = 0; j < e[i].size(); j++)
			c_e[c[i]].push_back(c[e[i][j]]);
	}

	for (int i = 1; i <= c_n; i++) {
		if (vis[i] == false) {
			gao(i);
		}
	}

	long long ans_r, ans_len;
	ans_r = ans_len = 0;
	for (int i = 0; i < m; i++) {
		int cid = c[d[str_m[i]]];
		ans_r += c_r[cid];
		ans_len += c_len[cid];
	}

	cout << ans_r << ' ' << ans_len << endl;
	return 0;
}