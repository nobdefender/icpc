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
        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    void build(vector<int>& a, int x, int lx, int rx)
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

    void build(vector<int>& a)
    {
        init(a.size());
        build(a, 0, 0, size);
        return;
    }

    int find(int k, int x, int lx, int rx)
    {
        if (rx == lx + 1)
        {
            return lx;
        }
        int m = (rx + lx) / 2;
        if (k < tree[2 * x + 1])
        {
            return find(k, 2 * x + 1, lx, m);
        }
        else
        {
            return find(k - tree[2 * x + 1], 2 * x + 2, m, rx);
        }
    }

    int find(int k)
    {
        return find(k, 0, 0, size);
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
            cin >> a;
            A[a] = 1 - A[a];
            tr.set(a, A[a]);
        }
        else
        {
            cin >> a;
            cout << tr.find(a) << endl;
        }
    }
    return 0;
}