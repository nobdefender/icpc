#include <iostream>
#include <vector>

using namespace std;

struct TreeMin
{
    struct node
    {
        long long seg, pref, suf, sum;
    };
    
    node combine(node a, node b)
    {
        return 
        {
            /*seg*/  max(a.seg, max(b.seg, a.suf+b.pref)),   
            /*pref*/ max(a.pref, a.sum+b.pref),
            /*suf*/  max(b.suf, b.sum+a.suf),
            /*sum*/  a.sum+b.sum
        };
    }

    const node ZERO = {0,0,0,0};

    node one_eleme(int x)
    {
        return {
            max(x,0),  //seg
            max(x,0),  //pref
            max(x,0),  //suf
            x          //sum
        };
    }

    vector<node> tree;
    int size;

    void init(int n)
    {
        size = 1;
        while (size < n)
        {
            size *= 2;
        }
        tree.assign(2 * size - 1, {0,0});
    }

    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            tree[x] = one_eleme(v);
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
        tree[x] = combine(tree[2*x+1],tree[2*x+2]);
    }

    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }

    
    void build(vector<int>&a, int x, int lx, int rx)
    {
        if (rx-lx==1)
        {
            if (lx<a.size())
            {
                tree[x] = one_eleme(a[lx]);
                
            }
        }
        else 
        {
            int m = (lx+rx)/2;
            build (a, 2*x+1,lx,m);
            build (a, 2*x+2,m,rx);
            tree[x] = combine(tree[2*x+1],tree[2*x+2]);
        }
    }

    void build(vector<int>&a)
    {
        init(a.size());
        build(a,0,0,size);
        return;
    }

    node calc(int l, int r, int x, int lx, int rx)
    {
        if (l>=rx || lx>=r)
        {
            return ZERO;
        }   
        if (lx>=l&&rx<=r)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        node sum1 = calc(l, r, 2 * x + 1, lx, m);
        node sum2 = calc(l, r, 2 * x + 2, m, rx);
        return combine(sum1, sum2);
    }

    node calc(int l, int r)
    {
        return calc(l, r, 0, 0, size);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    TreeMin tr;
    int n,m;
    cin>>n>>m;
    vector<int> A(n);
    for (int i = 0; i < n; i++)
    {
        cin>>A[i];
    }
    tr.build(A);
    int v,a,b;
    cout<<tr.tree[0].seg<<endl;
    for (int i = 0; i < m; i++)
    {
        cin>>a>>b;
        tr.set(a,b);
        cout<<tr.tree[0].seg<<endl;
    }
    return 0;   


}