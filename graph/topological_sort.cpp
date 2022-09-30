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

vector<bool> used;
vector<int> ans;
vector<vector<int>>g;


void dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
    }
    ans.push_back(v);
}

void topological_sort(int n) {
    used.assign(n, false);
    ans.clear();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    reverse(ans.begin(), ans.end());
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long t = 1;
    cin >> t;

    while (t--) {
        int n; // число вершин
        cin >> n;
        used.assign(n, false);
        g.resize(n);
        topological_sort(n);
    }

    return 0;
}