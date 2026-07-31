#define mod 1000000007
#define ll long long

ll pow_mod(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b % 2)
            res = (res * a) % mod;
        b /= 2;
        a = (a * a) % mod;
    }
    return res;
}

ll inv_mod(ll a) { return pow_mod(a, mod - 2); }

ll nCr(int n, int r, vector<ll>& fact, vector<ll>& inv) {
    if (r < 0 or r > n)
        return 0;
    return ((fact[n] * inv[r] % mod) * inv[n - r]) % mod;
}

int countValidSequences(int n, int k) {
    vector<long long> fact(n + 1), inv(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % mod;

    inv[n] = inv_mod(fact[n]);
    for (int i = n; i >= 1; i--) {
        inv[i - 1] = (inv[i] * i) % mod;
    }

    long long total = nCr(n - 1, k - 1, fact, inv);
    long long totalOdd = 0;
    if ((n - k) % 2 == 0) {
        totalOdd = nCr((n - k) / 2 + k - 1, k - 1, fact, inv);
    }
    return (total - totalOdd + mod) % mod;
}