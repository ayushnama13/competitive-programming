#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define vll vector<ll>
#define vit vector<int>
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
const ll MOD = 1e9 + 7;
#define el cout << endl;
#define rng(i, start, end) for (ll i = start; i <= end; i++)
#define gnr(i, start, end) for (ll i = start; i >= end; i--)
#define fast                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0)

template <typename T>
istream &operator>>(istream &in, vector<T> &vec)
{
    for (auto &element : vec)
    {
        in >> element;
    }
    return in;
}
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &vec)
{
    for (const auto &element : vec)
    {
        out << element << " ";
    }
    return out;
}

// ---------------------------------------------------------------- utilities

// base^k mod m
ll modpow(ll base, ll k, ll m = MOD)
{
    ll res = 1;
    base %= m;
    while (k > 0)
    {
        if (k & 1)
            res = res * base % m;
        base = base * base % m;
        k >>= 1;
    }
    return res;
}

// smallest non-negative integer not present in v
int mex(vector<int> &v)
{
    int n = v.size();
    vll seen(n + 2, 0);
    for (int x : v)
    {
        if (x >= 0 && x <= n + 1)
            seen[x] = 1;
    }
    for (int i = 0; i <= n + 1; i++)
    {
        if (seen[i] == 0)
            return i;
    }
    return n + 2;
}

// ------------------------------------------------------------- number theory

// Method 1: smallest-prime-factor table, for n <= 1e6.
//   build_spf();  int n; cin >> n;  vector<int> div = get_divisors(n);
const int MAXN = 1e6;
int spf[MAXN + 1];

void build_spf()
{
    for (int i = 1; i <= MAXN; i++)
    {
        spf[i] = i;
    }
    for (int i = 2; i * i <= MAXN; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= MAXN; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

vector<int> get_divisors(int n) // only for n <= 1e6, divisors are unsorted
{
    vector<pair<int, int>> factors;
    while (n > 1)
    {
        int p = spf[n], cnt = 0;
        while (n % p == 0)
        {
            n /= p;
            cnt++;
        }
        factors.push_back({p, cnt});
    }
    vector<int> divisors = {1};
    for (auto [p, cnt] : factors)
    {
        int sz = divisors.size();
        int mul = 1;
        for (int i = 0; i < cnt; i++)
        {
            mul *= p;
            for (int j = 0; j < sz; j++)
            {
                divisors.push_back(divisors[j] * mul);
            }
        }
    }
    return divisors;
}

// Method 2: sieve + trial division, for n <= 1e12 (primes up to 1e6).
//   sieve();  auto pf = prime_factorize(n);
//   vll divs; gen_div(0, 1, pf, divs);
vector<int> primes;
void sieve(int n = 1e6)
{
    vector<bool> isprime(n + 1, true);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (isprime[i])
        {
            primes.push_back(i);
            if ((long long)i * i <= n)
            {
                for (int j = i * i; j <= n; j += i)
                {
                    isprime[j] = false;
                }
            }
        }
    }
}

vector<pair<ll, int>> prime_factorize(ll n)
{
    vector<pair<ll, int>> pf;
    for (ll p : primes)
    {
        if (p * p > n)
            break;
        if (n % p == 0)
        {
            int cnt = 0;
            while (n % p == 0)
            {
                n /= p;
                cnt++;
            }
            pf.push_back({p, cnt});
        }
    }
    if (n > 1)
        pf.push_back({n, 1});
    return pf;
}

void gen_div(int idx, ll curr, vector<pair<ll, int>> &pf, vector<ll> &divs)
{
    if (idx == (int)pf.size())
    {
        divs.push_back(curr);
        return;
    }
    ll p = pf[idx].first;
    int e = pf[idx].second;
    for (int i = 0; i <= e; i++)
    {
        gen_div(idx + 1, curr, pf, divs);
        curr *= p;
    }
}

// ------------------------------------------------------------------- solve

void solve()
{
}

int main()
{
    fast;
    int testcases = 1;
    cin >> testcases;

    for (int I = 0; I < testcases; I++)
    {
        solve();
        el;
    }
    return 0;
}
