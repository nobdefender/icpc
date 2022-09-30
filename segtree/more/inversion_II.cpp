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

    int find(int k, int x, int lx, int rx)
    {
        if (rx == lx + 1)
        {
            return lx;
        }
        int m = (rx + lx) / 2;
        if (k < tree[2 * x + 2])
        {
            return find(k, 2 * x + 2, m, rx);
        }
        else
        {
            return find(k - tree[2 * x + 2], 2 * x + 1, lx, m);
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
    cin >> n;
      
    vector<int> A(n), P(n), E(n,1);

    tr.build(E);

    for (int i = 0; i < n; i++)
    {
        cin>>A[i];
    }
    int pos = 0;
    for (int i = n-1; i >=0 ; i--)
    {
        pos = tr.find(A[i]);
        P[i] = pos+1;
        tr.set(pos, 0);
    }
    for (int i = 0; i < n; i++)
    {
        cout<<P[i]<<" ";
    }
    
    return 0;
}