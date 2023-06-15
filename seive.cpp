vector<ll> prime(101, 1LL);

// prime[1] is set 1
void sieve(ll n)
{
    for (ll p = 2; p * p <= n; p++)
        if (prime[p])
            for (ll i = p * p; i <= n; i += p)
                prime[i] = 0;
}