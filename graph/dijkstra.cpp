// #include <iostream> //за O(N^2 + M) между двумя вершинами с восстановлением ответа
// #include <fstream>
// #include <iomanip>
// #include <ctime>
// #include "math.h"
// #include <algorithm>
// #include <vector>
// #include <map>

// using namespace std;

// int main() {
//     int n = 0, begin = 0, end = 0, inf = 10e4, temp = 0;
//     cin >> n;

//     vector<int> d(n, inf);
//     vector<int> p(n);
//     vector<bool> used(n, false);
//     vector <int> way;
//     vector <vector<int>> mass(n);

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> temp;
//             //mass.push_back(i);
//             //mass.push_back(j);
//             if (temp == 1) {
//                 mass[i].push_back(j);
//                 mass[j].push_back(i);
//             }
//         }
//     }
//     cin >> begin >> end;
//     begin--;
//     end--;

//     d[begin] = 0;

//     //cout << " test " << d[-1] << endl;

//     for (int i = 0; i < n; i++) {
//         int v = -1;
//         for (int j = 0; j < n; j++) {
//             if (!used[j] && (v == -1 || d[j] < d[v])) {
//                 v = j;
//             }
//         }
//         if (d[v] == inf) {
//             break;
//         }
//         used[v] = true;

//         for (int j = 0; j < mass[v].size(); j++) {
//             if (d[v] + 1 < d[mass[v][j]]) {
//                 d[mass[v][j]] = d[v] + 1;
//                 p[mass[v][j]] = v;
//             }
//         }
//     }

//     if (d[end] == inf) {
//         cout << -1 << endl;
//         return 0;
//     }

//     if (d[end] == 0) {
//         cout << 0 << endl;
//         return 0;
//     }

//     cout << d[end] << endl;

//     /*
//     for (int i = 0; i < p.size(); i++) {
//         cout << p[i] << " ";
//     }
//     cout << endl;
//     */

//     for (int v = end; v != begin; v = p[v]) {
//         way.push_back(v + 1);
//     }
//     way.push_back(begin + 1);

//     //reverse(way.begin(), way.end());

//     for (int i = way.size() - 1; i >= 0; i--) {
//         cout << way[i] << " ";
//     }

//     return 0;
// }

#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<iomanip>
#include<queue>

#define int long long
#define all(x) (x).begin(), (x).end()

using namespace std;

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long t = 1;
    // cin >> t;

    while (t--) {
        int inf = 1e18;
        int n = 0, m = 0;
        cin >> n >> m;
        vector<vector<pair<int, int>>> g(n);
        for (int i = 0; i < m; i++) {
            int to = 0, from = 0, len = 0;
            cin >> from >> to >> len;
            g[from - 1].push_back({to - 1, len});
            g[to - 1].push_back({from - 1, len});
        }

        vector<int> d(n, inf);
        vector<int> p(n);
        int from = 0, to = 0;
        d[0] = 0;
        priority_queue<pair<int, int>> q;
        q.push({ 0, 0 });
        while (!q.empty()) {
            int v = q.top().second;
            int cur_d = -q.top().first;
            q.pop();
            if (cur_d > d[v]) {
                continue;
            }

            for (int i = 0; i < g[v].size(); i++) {
                int to = g[v][i].first;
                int length = g[v][i].second;
                if (d[v] + length < d[to]) {
                    d[to] = d[v] + length;
                    p[to] = v;
                    q.push({ -d[to], to });
                }

            }
        }

        if (d[n - 1] == inf) {
            cout << -1 << endl;
            return 0;
        }

        if (!d[n - 1]) {
            cout << 0 << endl;
            return 0;
        }

        // cout << d[n - 1] << endl;

        vector<int> way;
        for (int v = n - 1; v != 0; v = p[v]) {
            way.push_back(v + 1);
        }
        way.push_back(1);

        //reverse(way.begin(), way.end());

        for (int i = way.size() - 1; i >= 0; i--) {
            cout << way[i] << " ";
        }

    }

    return 0;
}