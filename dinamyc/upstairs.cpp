#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;

    cin >> n;

    vector <int> coin(n, 0);
    vector <int> dp(n + 1, 0);

    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i >= 2) {
            dp[i] = max(dp[i], dp[i - 2]);
        }
        dp[i] += coin[i - 1];

    }

    cout << dp[n];

    return 0;
} 
