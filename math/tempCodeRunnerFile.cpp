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

vector<vector<int>> matrix_production(vector<vector<int>>& a, vector<vector<int>>& b) {
    vector<vector<int>> result(a.size(), vector<int>(b[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
                // if (mod) result[i][j] %= mod;
            }
        }
    }
    return result;
}

vector<vector<int>> fast_pow(vector<vector<int>>& a, int n) {
    if (n == 0) {
        vector<vector<int>> temp(a.size(), vector<int>(a[0].size()));
        for (int i = 0; i < a.size(); i++) {
            temp[i][i] = 1;
        }
        return temp;
    }
    if (n % 2 == 1) {
        vector<vector<int>> temp = fast_pow(a, n - 1);
        return matrix_production(temp, a);
    }
    else {
        vector<vector<int>> b = fast_pow(a, n / 2);
        return matrix_production(b, b);
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
        int n = 0, m = 0;
        cin >> n >> m;
        vector<vector<int>> mass(2, vector<int>(2));
        mass[0][0] = 0;
        mass[0][1] = 1;
        mass[1][0] = 1;
        mass[1][1] = 1;

        if (n == 1) {
            cout << 0 << endl;
            return 0;
        }
        else if (n == 2) {
            cout << 1 << endl;
            return 0;
        }
        else if (n == 3) {
            cout << 1 << endl;
            return 0;
        }

        vector<vector<int>> powed = fast_pow(mass, n - 4);
        int result = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result += powed[i][j];
            }
        }

        cout << result % m << endl;

    }

    return 0;
}