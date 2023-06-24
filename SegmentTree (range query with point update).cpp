#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ull unsigned long long int
#define pb push_back
#define xx first
#define yy second

// make sure to change the size
vector <ll> v(100001), seg(4 * 100001);

class segTree {

public:

	void build_max(ll i, ll l_range, ll r_range) {

		if (l_range == r_range) {
			seg[i] = v[r_range];
			return;
		}

		ll mid = l_range + (r_range - l_range) / 2LL;

		this->build_max((2LL * i) + 1LL, l_range, mid);
		this->build_max((2LL * i) + 2LL, mid + 1LL, r_range);

		seg[i] = max(seg[(2LL * i) + 1LL], seg[(2LL * i) + 2LL]);
	}

	ll query_max(ll i, ll l_range, ll r_range, ll l_query, ll r_query) {

		if ((r_range < l_query) || (l_range > r_query))
			return -1e16;

		if ((l_range >= l_query) && (r_range <= r_query)) {
			return seg[i];
		}

		ll mid = l_range + (r_range - l_range) / 2LL;
		ll leftSeg = this->query_max((2LL * i) + 1LL, l_range, mid, l_query, r_query);
		ll rightSeg = this->query_max((2LL * i) + 2LL, mid + 1LL, r_range, l_query, r_query);

		return max(leftSeg, rightSeg);
	}

	//increase the value at node index by val
	//if it is a point update make sure you remove the lazy vector
	void pointUpdate_max(ll i, ll l_range, ll r_range, ll node, ll val) {

		if (l_range == r_range) {
			seg[i] += val;
		}
		else {

			ll mid = l_range + (r_range - l_range) / 2LL;

			if ((node >= l_range) && (node <= mid)) {
				this->pointUpdate_max((2LL * i) + 1LL, l_range, mid, node, val);
			}
			else {
				this->pointUpdate_max((2LL * i) + 2LL, mid + 1LL, r_range, node, val);
			}

			seg[i] = max(seg[(2LL * i) + 1LL] , seg[(2LL * i) + 2LL]);
		}
	}

	void build_min(ll i, ll l_range, ll r_range) {

		if (l_range == r_range) {
			seg[i] = v[r_range];
			return;
		}

		ll mid = l_range + (r_range - l_range) / 2LL;

		this->build_min((2LL * i) + 1LL, l_range, mid);
		this->build_min((2LL * i) + 2LL, mid + 1LL, r_range);

		seg[i] = min(seg[(2LL * i) + 1LL], seg[(2LL * i) + 2LL]);
	}

	ll query_min(ll i, ll l_range, ll r_range, ll l_query, ll r_query) {

		if ((r_range < l_query) || (l_range > r_query))
			return 1e16;

		if ((l_range >= l_query) && (r_range <= r_query)) {
			return seg[i];
		}

		ll mid = l_range + (r_range - l_range) / 2LL;
		ll leftSeg = this->query_min((2LL * i) + 1LL, l_range, mid, l_query, r_query);
		ll rightSeg = this->query_min((2LL * i) + 2LL, mid + 1LL, r_range, l_query, r_query);

		return min(leftSeg, rightSeg);
	}

	//increase the value at node index by val
	//if it is a point update make sure you remove the lazy vector
	void pointUpdate_min(ll i, ll l_range, ll r_range, ll node, ll val) {

		if (l_range == r_range) {
			seg[i] += val;
		}
		else {

			ll mid = l_range + (r_range - l_range) / 2LL;

			if ((node >= l_range) && (node <= mid)) {
				this->pointUpdate_min((2LL * i) + 1LL, l_range, mid, node, val);
			}
			else {
				this->pointUpdate_min((2LL * i) + 2LL, mid + 1LL, r_range, node, val);
			}

			seg[i] = min(seg[(2LL * i) + 1LL] , seg[(2LL * i) + 2LL]);
		}
	}

	void build_sum(ll i, ll l_range, ll r_range) {

		if (l_range == r_range) {
			seg[i] = v[r_range];
			return;
		}

		ll mid = l_range + (r_range - l_range) / 2LL;

		this->build_sum((2LL * i) + 1LL, l_range, mid);
		this->build_sum((2LL * i) + 2LL, mid + 1LL, r_range);

		seg[i] = seg[(2LL * i) + 1LL] + seg[(2LL * i) + 2LL];
	}

	ll query_sum(ll i, ll l_range, ll r_range, ll l_query, ll r_query) {

		if ((r_range < l_query) || (l_range > r_query))
			return 0LL;

		if ((l_range >= l_query) && (r_range <= r_query)) {
			return seg[i];
		}

		ll mid = l_range + (r_range - l_range) / 2LL;
		ll leftSeg = this->query_sum((2LL * i) + 1LL, l_range, mid, l_query, r_query);
		ll rightSeg = this->query_sum((2LL * i) + 2LL, mid + 1LL, r_range, l_query, r_query);

		return leftSeg + rightSeg;
	}

	//increase the value at node index by val
	//if it is a point update make sure you remove the lazy vector
	void pointUpdate_sum(ll i, ll l_range, ll r_range, ll node, ll val) {

		if (l_range == r_range) {
			seg[i] += val;
		}
		else {

			ll mid = l_range + (r_range - l_range) / 2LL;

			if ((node >= l_range) && (node <= mid)) {
				this->pointUpdate_sum((2LL * i) + 1LL, l_range, mid, node, val);
			}
			else {
				this->pointUpdate_sum((2LL * i) + 2LL, mid + 1LL, r_range, node, val);
			}

			seg[i] = seg[(2LL * i) + 1LL] + seg[(2LL * i) + 2LL];
		}
	}
};

void solve()
{
	ll n, i;
	cin >> n;

	for (i = 0; i < n; i++) {
		cin >> v[i];
	}

	//Initialize segment tree
	segTree* sTree = new segTree;

	//build segement tree
	sTree->build_sum(0, 0, n - 1);

	ll q;
	cin >> q;

	sTree->pointUpdate_sum(0, 0, n - 1, 1, -40);

	while (q--) {
		ll l, r;
		cin >> l >> r;

		//make sure indexing is 0 based
		l--;
		r--;

		//query whichever the way you need
		cout << sTree->query_sum(0, 0, n - 1, l, r) << endl;
	}

	//make sure to clear these
	v.clear();
	seg.clear();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll t = 1;
	cin >> t;
	while (t--)
	{
		solve();
	}
}