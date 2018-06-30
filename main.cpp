#include <bits/stdc++.h>

using namespace std;

vector<int> ps;

struct Edge {
    int from = -1,
        to = -1,
        c = 0,
        f = 0,
        w = 0,
        num = 0;

    Edge *r = nullptr;

    Edge() {};

    Edge(int _from, int _to, int _c, int _w = 0, int _num = 0) {
        from = _from;
        to = _to;
        c = _c;
        w = _w;
        num = _num;
    }

    int wp() const {
        return w + ps[from] - ps[to];
    }
};

int n, m, k, s, t;
const int MX = 201;
const int INF = 2e+9;
vector<Edge *> gr[MX];
vector<Edge *> e;
vector<int> used(MX);

int fb() {
    vector<int> d(MX, INF);
    vector<Edge *> pr(MX);
    d[s] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 4 * m; ++j) {
            if (d[e[j]->from] < INF && e[j]->c - e[j]->f > 0) {
                if (d[e[j]->to] > d[e[j]->from] + e[j]->w) {
                    d[e[j]->to] = d[e[j]->from] + e[j]->w;
                    pr[e[j]->to] = e[j]->r;
                }
            }
        }
    }
    if (d[t] == INF) return INF;

    int now = t;
    while (now != s) {
        pr[now]->f -= 1;
        pr[now]->r->f += 1;
        now = pr[now]->to;
    }

    ps = d;
    return d[t];
}

int dij() {
    vector<int> d(MX, INF);
    vector<Edge *> pr(MX);
	d[s] = 0;

	set<pair<int, int>> st;
	st.insert({d[s], s});
	while (!st.empty()) {
		int now = st.begin()->second;
		st.erase(st.begin());

		for (int i = 0; i < gr[now].size(); ++i) {
			auto edge = gr[now][i];
			if (edge->c - edge->f > 0) {
                if (d[edge->to] > d[edge->from] + edge->wp()) {
                    st.erase({d[edge->to], edge->to});
                    d[edge->to] = d[edge->from] + edge->wp();
                    pr[edge->to] = edge->r;
                    st.insert({d[edge->to], edge->to});
                }
            }
		}
	}

	if (d[t] == INF) return INF;
    for (int i = 1; i <= n; ++i) {
        ps[i] = d[i]; /// neerc said it's ok
    }

    int real_ans = 0;

    int now = t;
    while (now != s) {
        pr[now]->f -= 1;
        pr[now]->r->f += 1;
        real_ans += pr[now]->r->w;
        now = pr[now]->to;
    }

    return real_ans;
}

bool dfs2(int v, vector<int> &way) {
    used[v] = true;
    if (v == t) return true;

    for (auto e : gr[v]) {
        if (!used[e->to] && e->f > 0) {
            way.push_back(e->num);
            if (dfs2(e->to, way)) {
                e->f -= 1;
                e->r->f += 1;
                return true;
            }
            way.pop_back();
        }
    }
    return false;
}

int main() {
    assert(freopen("brides.in", "r", stdin));

    cin >> n >> m >> k;
    s = 1, t = n;

    for (int i = 1; i <= m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        Edge *xtoy = new Edge(x, y, 1, w, i);
        Edge *rxtoy = new Edge(y, x, 0, -w, i);
        xtoy->r = rxtoy;
        rxtoy->r = xtoy;
        gr[x].push_back(xtoy);
        gr[y].push_back(rxtoy);

        Edge *ytox = new Edge(y, x, 1, w, i);
        Edge *rytox = new Edge(x, y, 0, -w, i);
        ytox->r = rytox;
        rytox->r = ytox;
        gr[y].push_back(ytox);
        gr[x].push_back(rytox);

        e.push_back(xtoy);
        e.push_back(ytox);
        e.push_back(rxtoy);
        e.push_back(rytox);
    }

    double res = 0;
    for (int i = 1; i <= k; ++i) {
        int localans;
        if (i == 1) {
            localans = fb();
        } else {
            localans = dij();
        }
        if (localans == INF) {
            cout << -1 << endl;
            return 0;
        } else {
            res += (double)localans / k;
        }
    }
    cout.precision(32);
    cout << res << endl;


    for (int TMP = 1; TMP <= k; ++TMP) {
        vector<int> way;
        dfs2(s, way);

        cout << way.size() << " ";

        for (auto i : way) {
            cout << i << " ";
        }
        cout << endl;

        used.clear();
        used.resize(n + 1);
    }
}
