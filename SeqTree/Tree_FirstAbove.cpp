#include <iostream>
#include <vector>

using namespace std;

struct TreeSum
{
    vector<long long> tree;
    int size;

    void init(int n)
    {
        size = 1;
        while (size < n)
        {
            size *= 2;
        }
        tree.assign(2 * size - 1, 0);
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, v, 2 * x + 2, m, rx);
        }
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
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
            tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
        }
    }

    void build(vector<int> &a)
    {
        init(a.size());
        build(a, 0, 0, size);
        return;
    }

    int first_above(int v, int x, int lx, int rx)
    {
        if (tree[x] < v)
            return -1;
        if (rx == lx + 1)
        {
            return lx;
        }
        int m = (lx + rx) / 2;
        int res = first_above(v, 2 * x + 1, lx, m);
        if (res == -1)
        {
            res = first_above(v, 2 * x + 2, m, rx);
        }
        return res;
    }

    int first_above(int v)
    {
        return first_above(v, 0, 0, size);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    TreeSum tr;
    int n, m;
    cin >> n >> m;
    vector<int> A(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
    }
    tr.build(A);
    int v, a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> v;
        if (v == 1)
        {
            cin >> a >> b;

            tr.set(a, b);
        }
        else
        {
            cin >> a;
            cout << tr.first_above(a) << endl;
        }
    }
    return 0;
}