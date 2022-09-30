#include <iostream>
#include <vector>

using namespace std;

struct TreeMin
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
        tree[x] = min(tree[2*x+1],tree[2*x+2]);
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
                tree[x] = a[lx];
                
            }
        }
        else 
        {
            int m = (lx+rx)/2;
            build (a, 2*x+1,lx,m);
            build (a, 2*x+2,m,rx);
            tree[x] = min(tree[2*x+1],tree[2*x+2]);
        }
    }

    void build(vector<int>&a)
    {
        init(a.size());
        build(a,0,0,size);
        return;
    }

    long long Min(int l, int r, int x, int lx, int rx)
    {
        if (l>=rx || lx>=r)
        {
            return INT_MAX;
        }   
        if (lx>=l&&rx<=r)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        long long sum1 = Min(l, r, 2 * x + 1, lx, m);
        long long sum2 = Min(l, r, 2 * x + 2, m, rx);
        return min(sum1, sum2);
    }

    long long Min(int l, int r)
    {
        return Min(l, r, 0, 0, size);
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
    for (int i = 0; i < m; i++)
    {
        cin>>v;
        if (v==1)
        {
            cin>>a>>b;
            tr.set(a,b);
        }
        else 
        {
            cin>>a>>b;
            cout<<tr.Min(a,b)<<endl;
        }
    }
    return 0;   


}