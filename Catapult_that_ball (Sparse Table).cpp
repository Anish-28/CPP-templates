#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define ull unsigned long long int 
#define pb push_back
#define xx first
#define yy second

ll n,log_two[100001],table[100001][26],a[100001];

void log_values(ll n)
{
    ll i;

    log_two[1] = 0;

    for (i = 2; i <= n; i++)
        log_two[i]=log_two[i/2]+1;
}

void build_sparse_table(ll n)
{
    ll i,p;

    for(i=0;i<n;i++)
    {
        table[i][0]=a[i];
    }

    for(p=1;p<=26;p++)
    {
        for(i=0;i+(1<<p)<=n;i++)
        {
            table[i][p]=max(table[i][p-1],table[i+(1<<(p-1))][p-1]);
        }
    }
}

ll sparse_query(ll l,ll r)
{
    ll max_pow=log_two[r-l+1];

    return max(table[l][max_pow],table[r-(1<<max_pow)+1][max_pow]);
}

int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	ll t=1;
	//cin>>t;
	while(t--)
	{
        ll i,q,ans=0;
        cin>>n>>q;

        for(i=0;i<n;i++)
        cin>>a[i];

        log_values(n);
        build_sparse_table(n);
        
        while(q--)
        {
            ll l,r;
            cin>>l>>r;
            l--;r--;
            
            if(abs(l-r)<=1)
                ans++;
            else
            {
                if(sparse_query(min(l,r)+1,max(l,r)-1)<=a[l])
                    ans++;
            }
        }

        cout<<ans<<'\n';
	}
}