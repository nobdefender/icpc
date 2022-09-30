#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> v;
vector<int> u;
queue<int> q;

void bfs(int i, int n) {
    q.push(i); u[i] = 1;
    while (!q.empty()) {
        int j = q.front(); q.pop();
        for (auto& x : v[j]) {
            if (!u[x]) {
                u[x] = 1;
                q.push(x);
            }
        }
        cout << j << ' ';
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    v.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        v[--x].push_back(--y);
        v[y].push_back(x);
    }
    for (int i = 0; i < n; i++) {
        u.assign(n, 0);
        bfs(i, n);
        cout << '\n';
    }
}