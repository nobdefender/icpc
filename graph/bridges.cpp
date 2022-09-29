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

vector<vector<int>> g;
vector<bool> used;
int timer = 0;
vector<int> tin, fup;
vector<pair<int, int>> result;

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (int i = 0; i < g[v].size(); i++) {
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
            if (fup[to] > tin[v]) {
                if (count(all(g[v]), to) == 1) {
                    result.push_back({ min(v, to), max(to, v) });
                }
            }
        }
    }
}

void find_bridges(int n) {
    timer = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
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
        g.resize(n);
        used.assign(n, false);
        tin.resize(n);
        fup.resize(n);
        cin.ignore();

        for (int i = 0; i < n; i++) {
            int current = 0, count = 0;
            cin >> current >> count;
            for (int j = 0; j < count; j++) {
                int temp = 0;
                cin >> temp;
                g[current].push_back(temp);
            }
        }

        find_bridges(n);
        if (result.size()) {
            sort(all(result));
            for (int i = 0; i < result.size(); i++) {
                cout << result[i].first << " " << result[i].second << endl;
            }
        }
        else {
            cout << "Empty" << endl;
        }
    }

    return 0;
}