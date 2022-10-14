// Построение суффиксного массива за O(n * log^2(n))

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    
    string str;
    cin >> str;
    str += "&";
    int len = str.length();
    vector<int> p(len), c(len);

    vector<pair<char, int>> a(len);
    for (int i = 0; i < len; i++)
    {
        a[i] = {str[i], i};
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < len; i++)
    {
        p[i] = a[i].second;
    }
    c[p[0]] = 0;
    for (int i = 1; i < len; i++)
    {
        if (a[i].first == a[i - 1].first)
        {
            c[p[i]] = c[p[i - 1]];
        }
        else
        {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    int k = 0;
    while ((1 << k) < len)
    {
        vector<pair<pair<int, int>, int>> a(len);

        for (int i = 0; i < len; i++)
        {
            a[i] = {{c[i], c[(i + (1 << k)) % len]}, i};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < len; i++)
        {
            p[i] = a[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < len; i++)
        {
            if (a[i].first == a[i - 1].first)
            {
                c[p[i]] = c[p[i - 1]];
            }
            else
            {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
        k++;
    }

    for (int i = 0; i < len; i++)
    {
        cout << p[i] << " ";
    }
}