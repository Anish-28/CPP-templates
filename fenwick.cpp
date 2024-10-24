#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ull unsigned long long int
#define pb push_back
#define xx first
#define yy second

ll N=10;

vector<ll> fen(N,0);

void update(ll i, ll val)
{
    while (i <= N)
    {
        fen[i] += val;
        i = i + (i & (-i));
    }
}

ll till(ll i)
{
    ll sum = 0;

    while (i > 0)
    {
        sum += fen[i];
        i = i - (i & (-i));
    }

    return sum;
}

ll range(ll l, ll r)
{
    return till(r) - till(l - 1);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a[5]={2,4,3,4,5};

    for(ll i=0;i<5;i++)
        update(i+1,a[i]);
    //cout<<fen[1]<<endl;
    //cout<<range(1,3);
    update(4,-1);
    update(5,3);
    cout<<range(4,5)<<endl;
}
