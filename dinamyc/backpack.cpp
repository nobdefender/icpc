#include <iostream>
#include <vector>
#include <algorithm>
#define inf 1e9+7
#define infinf 1e18
#define int long long
#define double long double
#define nl "\n"
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int gcd(int a, int b) { if (a == 0) return b; else return gcd(b % a, a); }

vector <int> result;

void getResult(int k, int s, vector<vector<int>>& dp, vector<int>& mass) {
    if (dp[k][s] == 0) {
        return;
    }

    if (dp[k][s - 1] == dp[k][s]) {
        getResult(k, s - 1, dp, mass);
    }
    else {
        getResult(k - mass[s - 1], s - 1, dp, mass);
        result.push_back(s);
    }
}

signed main() {
    fast;
    int t = 1;
    //cin>>t;
    while (t--) {
        int n, w;
        cin >> n >> w;
        vector<int>m(n + 1);
        vector<int>c(n + 1);

        long long test = 0;
        for (int i = 0; i < n; ++i) {
            cin >> m[i] >> c[i];
            test += m[i];
        }

        test = min(test, w); // чтобы не было ml

        vector<vector<int>> dp(test + 1, vector<int>(n + 1, 0));
        for (int k = 1; k < n + 1; k++) {
            for (int i = 0; i < test + 1; i++) {
                for (int count = 0; count <= 1; count++) { // цикл до count <= (min(kolvo_predm[k (возможно сделать - 1)], test / c[i]) + 1) - с огранич. количеством предметов
                    // если неограниченное количество предметов за O(nW)
                    // dp[i][k] = dp[i][k - 1]
                    // if (m[k] <= i) {
                    //     dp[i][k] = max(dp[i][k], dp[i][j - m[k]] + c[k - 1]);
                    // }
                    if (i - m[k - 1] * count >= 0) {
                        dp[i][k] = max(dp[i][k], dp[i - m[k - 1] * count][k - 1] + c[k - 1] * count);
                    }
                }
            }
        }

        cout << dp[test][n] << endl;

        getResult(test, n, dp, m);


        for (int i = 0; i < result.size(); i++) {
            if (result[i] != 0) {
                cout << result[i] << " ";
            }
        }

    }
}
