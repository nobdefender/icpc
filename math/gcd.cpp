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

unsigned gcd_recursive(unsigned a, unsigned b)
{
    if (b)
        return gcd_recursive(b, a % b);
    else
        return a;
}

unsigned gcd_iterative_mod(unsigned a, unsigned b)
{
    while (b)
    {
        unsigned t = b;
        b = a % b;
        a = t;
    }
    return a;
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long t = 1;
    // cin >> t;

    while (t--) {
        // cout << gcd_iterative_mod(10, 4) << endl;
    }

    return 0;
}