#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ff first
#define ss second
#define nl "\n"
#define sp " "
#define yes "YES"
#define no "NO"
#define bool_out(x) (x ? yes : no)
#define ll long long
#define int ll

const int mod = 1e9 + 7;
const int pow_mod = 1e9 + 6;

const int fft_mod = 7340033; // 7 * 2^20 + 1
const int fft_root = 5; // 5 ^ (2^20) == 1 mod 7340033
const int fft_root_1 = 4404020; // 5 * 4404020 == 1 mod 7340033
const int fft_pw = 1 << 20;

vector<int> fft(vector<int> a, bool invert = 0) {
    int n = a.size();
    
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int root_len = invert ? fft_root_1 : fft_root;
        for (int i = len; i < fft_pw; i <<= 1)
            root_len = (root_len * root_len) % fft_mod;
        for (int i = 0; i < n; i += len) {
            int root = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = a[i + j + len / 2] * root % fft_mod;
                a[i + j] = (u + v) % fft_mod;
                a[i + j + len / 2] = (u - v + fft_mod) % fft_mod;
                root = (root * root_len) % fft_mod;
            }
        }
    }

    if (invert) {
        int _n = 1;
        for (int i = 1; i <= fft_mod - 2; i++) _n = (_n * n) % fft_mod;
        for (int i = 0; i < n; i++) a[i] = (a[i] * _n) % fft_mod;
    }
    
    return a;
}

void solve() {
    int n, m, s;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    s = 1; while (s < n * m) s <<= 1;
    a.resize(s); b.resize(s);

    vector<int> fa = fft(a), fb = fft(b), fc(fa.size());
    for (int i = 0; i < fa.size(); i++) fc[i] = fa[i] * fb[i];

    vector<int> c = fft(fc, 1);

    for (int i = 0; i < s; i++) cout << a[i] << ' '; cout << '\n';
    for (int i = 0; i < s; i++) cout << b[i] << ' '; cout << '\n';
    for (int i = 0; i < s; i++) cout << c[i] << ' '; cout << '\n';
}

signed main() {
    cin.tie(0); cout.tie(0);
    ios::sync_with_stdio(0);
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
}