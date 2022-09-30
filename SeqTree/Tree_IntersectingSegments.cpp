#include <iostream>
#include <vector>
#include <algorithm>
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
        tree[x] = tree[2*x+1]+tree[2*x+2];
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
            tree[x] = tree[2*x+1]+tree[2*x+2];
        }
    }

    void build(vector<int>&a)
    {
        init(a.size());
        build(a,0,0,size);
        return;
    }

    long long sum(int l, int r, int x, int lx, int rx)
    {
        


        if (l >= rx || lx >= r)
        {
            return 0;
        }
        if (lx >= l && rx <= r)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        long long sum1 = sum(l, r, 2 * x + 1, lx, m);
        long long sum2 = sum(l, r, 2 * x + 2, m, rx);
        return sum1 + sum2;
    }

    long long sum(int l, int r)
    {
        return sum(l, r, 0, 0, size);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    TreeSum tr;
    int n,m;
    cin>>n;
    tr.init(2*n);
    vector<int> pos(n,-1), otv(n,0);
    int a;
    vector<int> A(2*n);
    for (int i = 0; i < 2*n; i++)
    {
        cin>>A[i];
    }
    

    for (int i = 0; i < 2*n; i++)
    {
        a = A[i];
        if (pos[a-1]==-1) {
            pos[a-1]=i;
            tr.set(pos[a-1],1);
        }
        else{
            otv[a-1] = tr.sum(pos[a-1]+1,i);
            tr.set(pos[a-1],0);
            pos[a-1] = 0;
        }
    }
    pos.assign(n,-1);
    reverse(A.begin(), A.end());

    for (int i = 0; i < 2*n; i++)
    {
        a = A[i];
        if (pos[a-1]==-1) {
            pos[a-1]=i;
            tr.set(pos[a-1],1);
        }
        else{
            otv[a-1] += tr.sum(pos[a-1]+1,i);
            tr.set(pos[a-1],0);
            pos[a-1] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout<<otv[i]<<" ";
    }
    
    return 0;   


}