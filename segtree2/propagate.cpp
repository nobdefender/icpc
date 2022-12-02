#include <iostream>
#include <vector>
#include <cmath>
#define int long long
using namespace std;

struct TreeSum
{
    vector<long long> tree;
    int size;
    const int NO_OPERATION = LLONG_MIN;
    void init(int n)
    {
        size = 1;
        while (size < n)
        {
            size *= 2;
        }
        tree.assign(2 * size - 1, 0);
    }

    long long get(int i, int x, int lx, int rx)
    {
        propagate(x, lx, rx);
        if (rx - lx == 1)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        if (i < m)
        {
            return get(i, 2 * x + 1, lx, m);
        }
        else
        {
            return get(i, 2 * x + 2, m, rx);
        }
    }

    long long get(int i)
    {
        return get(i, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < a.size())
            {
                tree[x] = a[lx];
            }
        }
        else
        {
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        }
    }

    void build(vector<int> &a)
    {
        init(a.size());
        build(a, 0, 0, size);
        return;
    }

    void propagate(int x, int lx, int rx)
    {
        if (tree[x] == NO_OPERATION)
            return;
        if (rx - lx == 1)
            return;
        tree[2 * x + 1] = tree[x];
        tree[2 * x + 2] = tree[x];
        tree[x] = NO_OPERATION;
    }
    void modify(int l, int r, int v, int x, int lx, int rx)
    {
        propagate(x, lx, rx);
        if (l >= rx || lx >= r)
        {
            return;
        }
        if (lx >= l && rx <= r)
        {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
    }

    void modify(int l, int r, int v)
    {
        return modify(l, r, v, 0, 0, size);
    }
};

signed main()
{
    ios::sync_with_stdio(false);
    TreeSum tr;
    int n, m;
    cin >> n >> m;
    tr.init(n);
    int v, l, r, j;
    for (int i = 0; i < m; i++)
    {
        cin >> v;
        if (v == 1)
        {
            cin >> l >> r >> j;
            tr.modify(l, r, j);
        }
        else
        {
            cin >> j;
            cout << tr.get(j) << endl;
        }
    }
    return 0;
}