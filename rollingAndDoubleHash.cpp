// Lucky Primes
// 1000010801
// 1000010281ß

void rabinKarp(string s, string pat, ll mod, ll base) {

    int n = s.size();
    int m = pat.size();

    ll patHash = 0;
    ll curHash = 0;

    ll power = 1;

    for (int i = 0; i < m - 1; i++) {

        power = (power * base) % mod;
    }

    for (int i = 0; i < m; i++) {

        patHash = (patHash * base + pat[i]) % mod;

        curHash = (curHash * base + s[i]) % mod;
    }

    for (int i = 0; i <= n - m; i++) {

        if (patHash == curHash) {

            bool ok = true;

            for (int j = 0; j < m; j++) {

                if (s[i + j] != pat[j]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {

                cout << "Pattern found at index " << i << endl;
            }
        }

        if (i < n - m) {

            ll rem = (s[i] * power) % mod;

            curHash = (base * ((curHash - rem + mod) % mod) + s[i + m]) % mod;
        }
    }
}

void rabinKarp(string s, string pat, ll modA, ll baseA, ll modB, ll baseB) {

    int n = s.size();
    int m = pat.size();

    ll patHashA = 0;
    ll patHashB = 0;

    ll curHashA = 0;
    ll curHashB = 0;

    ll powA = 1;
    ll powB = 1;

    for (int i = 0; i < m - 1; i++) {

        powA = (powA * baseA) % modA;
        powB = (powB * baseB) % modB;
    }

    for (int i = 0; i < m; i++) {

        patHashA = (patHashA * baseA + pat[i]) % modA;

        curHashA = (curHashA * baseA + s[i]) % modA;

        patHashB = (patHashB * baseB + pat[i]) % modB;

        curHashB = (curHashB * baseB + s[i]) % modB;
    }

    for (int i = 0; i <= n - m; i++) {

        if (patHashA == curHashA && patHashB == curHashB) {

            bool ok = true;

            for (int j = 0; j < m; j++) {

                if (s[i + j] != pat[j]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {

                cout << "Pattern found at index " << i << endl;
            }
        }

        if (i < n - m) {

            ll remA = (s[i] * powA) % modA;

            curHashA =
                (baseA * ((curHashA - remA + modA) % modA) + s[i + m]) % modA;

            ll remB = (s[i] * powB) % modB;

            curHashB =
                (baseB * ((curHashB - remB + modB) % modB) + s[i + m]) % modB;
        }
    }
}