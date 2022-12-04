#include <iostream>
#include <vector>

#define int long long

using namespace std;

struct TreeSeg
{
    struct block
    {
        int seg, pref, suf, sum;
    };
    struct node
    {
        int set;
        block segsum;
    };
    block combine(block a, block b)
    {
        return {
            /*seg*/ max(a.seg, max(b.seg, a.suf + b.pref)),
            /*pref*/ max(a.pref, a.sum + b.pref),
            /*suf*/ max(b.suf, b.sum + a.suf),
            /*sum*/ a.sum + b.sum};
    }
    vector<node> tree;
    block ZERO = {0, 0, 0, 0};
    int size;
    int NETRAL = 0;
    int NO_OPERATION = LLONG_MIN;
    
    block one_eleme(int x)
    {
        return {
            max(x, (long long)0), // seg
            max(x, (long long)0), // pref
            max(x, (long long)0), // suf
            x                     // sum
        };
    }

    int operat_modify(int a, int b, int len)
    {
        if (b == NO_OPERATION)
            return a;
        return b * len;
    }
    block operat_modify(block a, int b, int len)
    {
        if (b == NO_OPERATION)
            return a;
        int sum = b * len;
        if (b > 0)
        {
            return {sum, sum, sum, sum};
        }
        else
        {
            return {0,0,0,sum};
        }
    }
    int operat_min(int a, int b)
    {
        return a + b;
    }
    void propagate(int x, int lx, int rx)
    {
        if (tree[x].set == NO_OPERATION || rx - lx == 1)
            return;
        int m = (lx + rx) / 2;
        tree[2 * x + 1].set = operat_modify(tree[2 * x + 1].set, tree[x].set, 1);
        tree[2 * x + 1].segsum = operat_modify(tree[2 * x + 1].segsum, tree[x].set, m - lx);
        tree[2 * x + 2].set = operat_modify(tree[2 * x + 1].set, tree[x].set, 1);
        tree[2 * x + 2].segsum = operat_modify(tree[2 * x + 1].segsum, tree[x].set, rx - m);
        tree[x].set = NO_OPERATION;
    }
    void init(int n)
    {
        size = 1;
        while (size < n)
        {
            size *= 2;
        }
        tree.assign(2 * size - 1, {0, 0});
    }

    node calc(int l, int r, int x, int lx, int rx)
    {
        propagate(x, lx, rx);
        if (l>=rx || lx>=r)
        {
            return {0,ZERO};
        }   
        if (lx>=l&&rx<=r)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        node sum1 = calc(l, r, 2 * x + 1, lx, m);
        node sum2 = calc(l, r, 2 * x + 2, m, rx);
        return {sum1.set+sum2.set,combine(sum1.segsum, sum2.segsum)};
    }

    node calc(int l, int r)
    {
        return calc(l, r, 0, 0, size);
    }

    void build(vector<int> &a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < a.size())
            {
                tree[x].segsum.sum = a[lx];
            }
        }
        else
        {
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            tree[x].segsum = combine(tree[2 * x + 1].segsum, tree[2 * x + 2].segsum);
        }
    }

    void build(vector<int> &a)
    {
        init(a.size());
        build(a, 0, 0, size);
        return;
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
            tree[x].set = operat_modify(tree[x].set, v, 1);
            tree[x].segsum = operat_modify(tree[x].segsum, v, (rx - lx));
            return;
        }
        int m = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, m);
        modify(l, r, v, 2 * x + 2, m, rx);
        tree[x].segsum = combine(tree[2 * x + 1].segsum, tree[2 * x + 2].segsum);
    }

    void modify(int l, int r, int v)
    {
        return modify(l, r, v, 0, 0, size);
    }
};

signed main()
{
    ios::sync_with_stdio(false);
    TreeSeg tr;
    int n, m;
    cin >> n >> m;
    tr.init(n);
    vector<int> a(n, 0);
    tr.build(a);
    int v, l, r, j;
    for (int i = 0; i < m; i++)
    {
        cin >> l>>r>>v;
        tr.modify(l,r,v);
        cout<<tr.tree[0].segsum.seg<<endl;
    }
    return 0;
}