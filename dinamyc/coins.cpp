#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int sum = 0, n = 0;

    cin >> sum >> n;
    vector <int> coin(n);
    vector <int> res(sum+1, 1e9);

    res[0] = 0;

    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    for (int i = 1; i <= sum; i++) {
        for (int j = 0; j < n; j++) {
            if (i - coin[j] >= 0) {
                res[i] = min(res[i], res[i - coin[j]] + 1);
            }
        }
    }

    if (res[sum] == 1e9) {
        cout << "0";
    }
    else {
        cout << res[sum];
    }
    
    return 0;
}
