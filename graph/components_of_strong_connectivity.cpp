#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<iomanip>

#define int long long
#define all(x) (x).begin(), (x).end()

using namespace std;

vector < vector<int> > g, gr;
vector<char> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        if (!used[g[v][i]]) {
            dfs1(g[v][i]);
        }
    }

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (size_t i = 0; i < gr[v].size(); ++i) {
        if (!used[gr[v][i]]) {
            dfs2(gr[v][i]);
        }
    }
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long t = 1;
    // cin >> t;

    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int a = 0, b = 0;
            cin >> a >> b;
            g[a].push_back(b);
            gr[b].push_back(a);
        }

        used.assign(n, false);
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs1(i);
            }
        }

        used.assign(n, false);
        for (int i = 0; i < n; ++i) {
            int v = order[n - 1 - i];
            if (!used[v]) {
                dfs2(v);
                for (int j = 0; j < component.size(); j++) {
                    cout << component[i] << " ";
                }
                cout << endl;
                component.clear();
            }
        }
    }


    return 0;
}