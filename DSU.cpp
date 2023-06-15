vector<ll> par(100001), rk(100001);

void dsuInit(ll n)
{
    for (ll i = 1; i <= n; i++)
        par[i] = i;
}

ll findPar(ll node)
{
    if (node == par[node])
        return node;

    return par[node] = findPar(par[node]);
}

void Union(ll x, ll y)
{
    ll xPar = findPar(x), yPar = findPar(y);

    if (rk[xPar] < rk[yPar])
        par[xPar] = yPar;
    else if (rk[xPar] > rk[yPar])
        par[yPar] = xPar;
    else
    {
        par[yPar] = xPar;
        rk[xPar]++;
    }
}
