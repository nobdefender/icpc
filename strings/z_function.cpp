#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    string s = "";
    cin >> s;
    vector<int> z(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (z[i] + i < s.size() && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (z[i] + i - 1 > r) {
            l = i;
            r = z[i] + i - 1;
        }

    }

    for (int i = 0; i < z.size(); i++)
    {
        cout << z[i] << " ";
    }


}