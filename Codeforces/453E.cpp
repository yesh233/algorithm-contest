#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

const int MAX_N = 1e5 + 100;

long long n, m;
long long s[MAX_N], c[MAX_N], d[MAX_N];
long long t, l, r;
map< pair<long long, long long>, long long > segs; 
vector< pair< pair<long long, long long>, pair<long long, long long> > > queries;
long long incs[MAX_N], maxs[MAX_N];
long long res[MAX_N];

void insert(long long a[], long long x, long long t) {
    for ( ; x < MAX_N; x += x & (-x)) {
	a[x]  += t;
    }
}

long long query(long long a[], long long x) {
    long long ret = 0;
    for ( ; x; x -= x & (-x)) {
	ret += a[x];
    }
    return ret;
}

long long query(long long a[], long long l, long long r) {
    return query(a, r) - query(a, l-1);
}

int main () {
    cin >> n;
    for (int i = 1; i <= n; i++) {
	cin >> s[i] >> c[i] >> d[i];
        segs[make_pair(i, i)] = -1;
	if (d[i] > 0) {
	    insert(incs, i, d[i]);
	    queries.push_back(make_pair(make_pair(c[i]/d[i]+1, -1),
		    make_pair(i,i)));
	}
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
	cin >> t >> l >> r;
	while (true) {
	    map< pair<long long, long long>, long long > ::iterator
		it = segs.upper_bound(make_pair(r, MAX_N));
	    if (it == segs.begin()) break;
	    it--;
	    if (it->first.second < l) {
		break;
	    }else if (it->first.second > r) {
		segs[make_pair(it->first.first,r)] = it->second;
                segs[make_pair(r+1, it->first.second)] = it->second;
	    }else if (it->first.first < l) { 
		segs[make_pair(it->first.first, l-1)] = it->second;
		segs[make_pair(l, it->first.second)] = it->second;
	    }else if (it->second == -1) {
		int id = it->first.first;
		res[i] += min(c[id], s[id]+d[id]*t);
	    }else {
		queries.push_back(make_pair(make_pair(t-it->second, i),
			it->first));
	    }
	    segs.erase(it);
	}
	
	segs[make_pair(l,r)] = t;
/*
	map< pair<long long, long long>, long long > ::iterator it;
        for (it = segs.begin(); it != segs.end(); it++) {
	    cout << it->first.first << ' ' << it->first.second << ' ' << it->second << endl;
	}
	*/
    }

    sort(queries.begin(), queries.end());
    for (int i = 0; i < queries.size(); i++) {
	int type = queries[i].first.second;
        t = queries[i].first.first;
	l = queries[i].second.first;
	r = queries[i].second.second;
        if (type == -1) {
	    insert(incs, l, -d[l]);
	    insert(maxs, l, c[l]);
	}else {
	    res[type] += t * query(incs, l, r) + query(maxs, l, r);
	}
    }

    for (int i = 1; i <= m; i++) {
	cout << res[i] << endl;
    }


    return 0;
}
