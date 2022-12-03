#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<stack>
#include<iomanip>

#define int long long
#define all(x) (x).begin(), (x).end()
#define endl "\n"

using namespace std;

vector<vector<pair<int, int>>> mst;
vector<int> parent;
vector<pair<int, pair<int, int>>> G;

int findRoot(int v) {
    return parent[v] == v ? v : parent[v] = findRoot(parent[v]);
}

bool connected(int v1, int v2) {
    return findRoot(v1) == findRoot(v2);
}

void merge(int v1, int v2) {
    int r1 = findRoot(v1), r2 = findRoot(v2);
    if (r1 == r2)
        return;
    if (rand() % 2)
        parent[r1] = r2;
    else
        parent[r2] = r1;
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long _t = 1;
    // cin >> _t;

    while (_t--) {
        int n = 0, m = 0;
        cin >> n >> m;
        mst.resize(n);
        for (int i = 0; i < m; i++) {
            int v = 0, u = 0, cost = 0;
            cin >> v >> u >> cost;
            v--;
            u--;
            G.push_back({ cost, {v, u} });
        }

        int cost = 0;
        int all_sum = 0;
        sort(all(G));
        parent.resize(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
        for (int i = 0; i < m; ++i) {
            int a = G[i].second.first, b = G[i].second.second, l = G[i].first;
            if (!connected(a, b)) {
                mst[G[i].second.first].push_back({ G[i].second.second, G[i].first });
                // mst[G[i].second.second].push_back({ G[i].second.first, G[i].first });
                merge(a, b);
                all_sum += G[i].first;
            }
        }

        cout << all_sum << endl;
        for (int i = 0; i < mst.size(); i++) {
            for (int j = 0; j < mst[i].size(); j++) {
                cout << i + 1 << " " << mst[i][j].first + 1 << endl;
            }
        }
    }

    return 0;
}