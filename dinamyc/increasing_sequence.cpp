#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() // за O(NlogN)
{
    int n = 0;
    cin >> n;
    vector <int> mass(n, 0);
    vector <int> dp(n + 1, 10e8);
    vector <int> path;
    vector<int> pos(n);
    vector<int> prev(n);

    for (int i = 0; i < n; i++) {
        cin >> mass[i];
    }

    dp[0] = -10e8;
    pos[0] = -1;

    int len = 0;

    for (int i = 0; i < n; i++) {
        int j = upper_bound(dp.begin(), dp.end(), mass[i]) - dp.begin();
        if (dp[j - 1] < mass[i] && mass[i] < dp[j]) {
            dp[j] = mass[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            len = max(len, j);
        }
    }

    cout << len << endl;

    int p = pos[len];
    while(p != -1) {
        path.push_back(mass[p]);
        p = prev[p];
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl;



    return 0;
}

// #include <iostream> // за O(N^2)
// #include <vector>
// #include <algorithm>

// using namespace std;

// int main()
// {
//     int n = 0;
//     cin >> n;
//     vector <int> mass(n, 0);
//     vector <int> dp(n, 1);
//     vector <int> p(n, -1);
//     vector <int> path;

//     for (int i = 0; i < n; i++) {
//         cin >> mass[i];
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < i; j++) {
//             if (mass[i] > mass[j]) {
//                 if (dp[j] + 1 > dp[i]) {
//                     dp[i] = dp[j] + 1;
//                     p[i] = j;
//                 }
//             }
//         }
//     }

//     int pos = max_element(dp.begin(), dp.end()) - dp.begin();

//     while (pos != -1) {
//         path.push_back(mass[pos]);
//         pos = p[pos];
//     }

//     cout << *max_element(dp.begin(), dp.end()) << endl;

//     reverse(path.begin(), path.end());
    
//     for (int i = 0; i < path.size(); i++) {
//         cout << path[i] << " ";
//     }
//     cout << endl;

//     return 0;
// }

