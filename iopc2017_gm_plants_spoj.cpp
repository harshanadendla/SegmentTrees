#include<bits/stdc++.h>
using namespace std;
#define ll long long int

int axis[3][400400];
int lazy[3][400400];

void update(ll idx,ll updateStart,ll updateEnd,ll treeStart,ll treeEnd,int c)
{
    if(lazy[c][idx])
    {
        axis[c][idx]=(treeEnd-treeStart+1)-axis[c][idx];
        if(treeStart!=treeEnd)
        {
            lazy[c][2*idx]^=1;
            lazy[c][2*idx+1]^=1;
        }
        lazy[c][idx]=0;
    }
    if(treeEnd<updateStart || treeStart>updateEnd || treeStart>treeEnd)
    {
        return ;
    }
    if(updateStart<=treeStart && updateEnd>=treeEnd)
    {
        axis[c][idx]=(treeEnd-treeStart+1)-axis[c][idx];
        if(treeStart!=treeEnd)
        {
            lazy[c][2*idx]^=1;
            lazy[c][2*idx+1]^=1;
        }
        return ;
    }
    ll mid=treeStart+(treeEnd-treeStart)/2;

    update(2*idx,updateStart,updateEnd,treeStart,mid,c);
    update(2*idx+1,updateStart,updateEnd,mid+1,treeEnd,c);
    axis[c][idx]=axis[c][2*idx]+axis[c][2*idx+1];
}

ll query(ll idx,ll queryStart,ll queryEnd,ll treeStart,ll treeEnd,int c)
{
    if(lazy[c][idx])
    {
        axis[c][idx]=(treeEnd-treeStart+1)-axis[c][idx];
        if(treeStart!=treeEnd)
        {
            lazy[c][2*idx]^=1;
            lazy[c][2*idx+1]^=1;
        }
        lazy[c][idx]=0;
    }
    if(treeEnd<queryStart || treeStart>queryEnd || treeStart>treeEnd)
    {
        return 0;
    }
    if(queryStart<=treeStart && queryEnd>=treeEnd)
    {
        return axis[c][idx];
    }
    ll mid=treeStart+(treeEnd-treeStart)/2;

    return query(2*idx,queryStart,queryEnd,treeStart,mid,c) + query(2*idx+1,queryStart,queryEnd,mid+1,treeEnd,c);
}

int main()
{
    ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
    int t;
    cin>>t;
    while(t--)
    {
        memset(axis,0,sizeof(axis));
        memset(lazy,0,sizeof(lazy));

        ll nx,ny,nz,q,a,b,temp,x1,x2,y1,y2,z1,z2;
        cin>> nx >> ny >> nz >> q;

        while(q--)
        {
            cin>>temp;
            if(temp==0)
            {
                cin>>a>>b;
                update(1,a+1,b+1,1,nx,0);
            }
            else if(temp==1)
            {
                cin>>a>>b;
                update(1,a+1,b+1,1,ny,1);
            }
            else if(temp==2)
            {
                cin>>a>>b;
                update(1,a+1,b+1,1,nz,2);
            }
            else
            {
                cin>> x1 >> y1 >> z1 >> x2 >> y2 >>z2 ;
                ll redx=query(1,x1+1,x2+1,1,nx,0);
                ll grnx=(x2-x1+1)-redx;

                ll redy=query(1,y1+1,y2+1,1,ny,1);
                ll grny=(y2-y1+1)-redy;

                ll redz=query(1,z1+1,z2+1,1,nz,2);
                ll grnz=(z2-z1+1)-redz;

                ll ans=(redx*grny*grnz)+(grnx*redy*grnz)+(grnx*grny*redz)+(redx*redy*redz);
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}