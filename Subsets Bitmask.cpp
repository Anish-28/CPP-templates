ll num = 1<<n;
ll pref[n+1]={0};
for(i=1;i<num;i++)
{
    ll pos=n-1;
    ll bitmask=i;
    ll ans=0;

    while(bitmask>0)
    {
        if((bitmask&1)==1)
            ans=(ans^a[pos])%mod;
        pos--;
        bitmask>>=1;
    }

    ll cnt=__builtin_popcount(i);
    pref[cnt]=(pref[cnt]+ans)%mod;
}