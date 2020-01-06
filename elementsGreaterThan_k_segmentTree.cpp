#include<bits/stdc++.h>
using namespace std;

struct node
{
    vector<int> array;
};

vector<node> tree(400400);
vector<int> a(400400);

vector<int> merges(vector<int> l,vector<int> r)
{
    vector<int> res;
    int i=0,j=0;
    while(i<l.size() && j<r.size())
    {
        if(l[i]<r[j])
        {
            res.push_back(l[i++]);
        }
        else
        {
            res.push_back(r[j++]);
        }
    }
    while(i<l.size())
    {
        res.push_back(l[i++]);
    }
    while(j<r.size())
    {
        res.push_back(r[j++]);
    }
    return res;
}

void build(int id,int treeStart,int treeEnd,vector<int> a,vector<node>& tree)
{
    if(treeStart==treeEnd)
    {
        tree[id].array.push_back(a[treeStart]);
        return ;
    }
    int mid=treeStart+(treeEnd-treeStart)/2;
    build(2*id+1,treeStart,mid,a,tree);
    build(2*id+2,mid+1,treeEnd,a,tree);
    tree[id].array=merges(tree[2*id+1].array,tree[2*id+2].array);
}

int query(int id,int treeStart,int treeEnd,int queryStart,int queryEnd,vector<node>& tree,int k)
{
    if(queryStart>treeEnd || queryEnd<treeStart || treeStart>treeEnd)
    {
        return 0;
    }
    if(queryStart<=treeStart && queryEnd>=treeEnd)
    {
        return tree[id].array.size()-(upper_bound(tree[id].array.begin(),tree[id].array.end(),k)-tree[id].array.begin());
    }
    int mid=treeStart+(treeEnd-treeStart)/2;
    return query(2*id+1,treeStart,mid,queryStart,queryEnd,tree,k) + query(2*id+2,mid+1,treeEnd,queryStart,queryEnd,tree,k);
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        fill_n(a.begin(),0,400400);
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        build(1,0,n-1,a,tree);
        int q;
        cin>>q;
        int l,r,k;
        for(int i=0;i<q;i++)
        {
            cin>>l>>r>>k;
            cout<<query(1,0,n-1,l,r,tree,k)<<"\n";
        }
    }
    return 0;
}