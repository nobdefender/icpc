#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string s = "";
    cin >> s;

    vector < vector<long long>> dp(s.length(), vector<long long>(s.length(), 0));

    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < s.length(); j++) {
            if ((i + j) == s.length()) {
                break;
            }
            if (j == i + j) {
                dp[j][i + j] = 1;
                continue;
            }
            if (s[j] == s[i + j]) {
                dp[j][i + j] = dp[j][i + j - 1] + dp[j + 1][i + j] + 1;
            }
            else {
                dp[j][i + j] = dp[j][i + j - 1] + dp[j + 1][i + j] - dp[j + 1][i + j - 1];
            }
        }
    }

    cout << dp[0][s.length() - 1] << endl;

    return 0;
}
