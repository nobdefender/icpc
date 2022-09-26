#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n = 0, last_i = 300, last_j = 300;
    char temp = ' ';
    cin >> n;

    vector<vector<int>> array(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> temp;
            array[i][j] = int(temp) - 48;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (i == 0) {
                array[i][j] = array[i][j - 1] + array[i][j];
                continue;

            }
            if (j == 0) {
                array[i][j] = array[i - 1][j] + array[i][j];
                continue;
            }

            array[i][j] = min(array[i][j] + array[i][j - 1], array[i][j] + array[i - 1][j]);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (i > last_i || j > last_j) {
                continue;
            }

            if (i == n - 1 && j == n - 1) {
                array[i][j] = -1;
                last_i = i;
                last_j = j;
            }

            if (i == 0) {
                array[i][j] = -1;
                last_i = i;
                last_j = j;
                continue;
            }

            if (j == 0 && (array[i][j + 1] == -1 || array[i + 1][j] == -1)) {
                array[i][j] = -1;
                last_i = i;
                last_j = j;
                continue;
            }
            
            if (array[i - 1][j] < array[i][j - 1]) {
                array[i - 1][j] = -1;
                last_i = i;
                last_j = j;
                break;
            }
            else {
                array[i][j - 1] = -1;
                last_i = i;
                last_j = j;
            }
        }

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                cout << "#";
                continue;
            }
            if (array[i][j] == -1) {
                cout << "#";
            }
            else {
                cout << "-";
            }
        }
        cout << endl;
    }


    return 0;
}
