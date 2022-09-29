#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<iomanip>
#include<fstream>

#define int long long
#define all(x) (x).begin(), (x).end()

using namespace std;

vector<vector<int>> g;
vector<bool> used;
int timer = 0;
vector<int> tin, fup;
set<int> result;


void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p) {
            continue;
        }
        if (used[to]) {
            fup[v] = min(fup[v], tin[to]);
        }
        else {
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
            if (fup[to] >= tin[v] && p != -1) {
                result.insert(v);
            }
            children++;
        }
    }

    if (p == -1 && children > 1) {
        result.insert(v);
    }
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long t = 1;
    // in >> t;

    while (t--) {
        int n, m, k;
        ifstream in;
        in.open("points.in");
        ofstream out;
        out.open("points.out");
        in >> n >> m;
        g.resize(n);
        used.assign(n, false);
        tin.resize(n);
        fup.resize(n);
        for (int i = 0; i < m; i++) {
            int first, second;
            in >> first >> second;
            first--;
            second--;
            g[first].push_back(second);
            g[second].push_back(first);
        }

        for (int i = 0; i < n; i++) {
            dfs(i);

        }

        out << result.size() << endl;
        for (auto it = result.begin(); it != result.end(); it++) {
            out << *it + 1 << " ";
        }

        out.close();
    }

    return 0;
}