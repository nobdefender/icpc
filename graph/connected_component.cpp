#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<vector<int>> &mass, vector<bool> &used, int vertex) {
    used[vertex] = true;
    for (int i = 0; i < mass[vertex].size(); i++) {
        if (used[mass[vertex][i]] == false) {
            dfs(mass, used, mass[vertex][i]);
        }
    }
}

int main()
{
    int n = 0, m = 0, second = 0, first = 0, result = 0;
    cin >> n >> m;
 
    vector<vector<int>> mass(n);
    vector<bool> used(n, false);

    for (int i = 0; i < m; i++) {
        cin >> first >> second;
        first--;
        second--;
        mass[first].push_back(second);
        mass[second].push_back(first);
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(mass, used, i);
            result++;
        }
    }

    cout << result << endl;

    return 0;
}
