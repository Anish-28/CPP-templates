#define mod 1000000007

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

ll inv_mod(ll a) {
    return pow_mod(a, mod - 2);
}