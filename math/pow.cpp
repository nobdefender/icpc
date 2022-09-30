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

int binpow(int a, int n) {
    int res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

vector<vector<int>> matrix_production(vector<vector<int>>& a, vector<vector<int>>& b, int mod) {
    vector<vector<int>> result(a.size(), vector<int>(b[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
                if (mod) result[i][j] %= mod;
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
        return matrix_production(temp, a, 1e7 + 7);
    }
    else {
        vector<vector<int>> b = fast_pow(a, n / 2);
        return matrix_production(b, b, 1e7 + 7);
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
        cout << binpow(12, 5) << endl;

    }

    return 0;
}