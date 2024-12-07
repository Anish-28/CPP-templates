#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ull unsigned long long int
#define pb push_back
#define xx first
#define yy second

// make sure to change the size
vector <ll> v(100001), seg(4 * 100001), lazy(4 * 100001);

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

	//increase the value of l to r by val
	void rangeUpdate_max(ll i, ll l_range, ll r_range, ll l_incr, ll r_incr, ll val) {

		//first update the lazy tree if needed
		if (lazy[i] != 0LL) {

			seg[i] += lazy[i];

			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += lazy[i];
				lazy[(2LL * i) + 2LL] += lazy[i];
			}

			lazy[i] = 0LL;
		}

		if ((r_incr < l_range) || (l_incr > r_range) || (l_range > r_range))
			return;

		//if seg tree range completely lies then add value to that node
		//and update values of child nodes of current node (propogate updates)
		if ((l_range >= l_incr) && (r_range <= r_incr)) {
			seg[i] += val;
			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += val;
				lazy[(2LL * i) + 2LL] += val;
			}
			return;
		}

		//partial overlap case
		ll mid = l_range + (r_range - l_range) / 2LL;
		this->rangeUpdate_max((2LL * i) + 1LL, l_range, mid, l_incr, r_incr, val);
		this->rangeUpdate_max((2LL * i) + 2LL, mid + 1LL, r_range, l_incr, r_incr, val);
		seg[i] = max(seg[(2LL * i) + 1LL] , seg[(2LL * i) + 2LL]);
	}

	//use this if you are using rangeUpdate_max
	ll query_maxLazy(ll i, ll l_range, ll r_range, ll l_incr, ll r_incr) {

		//first update the lazy tree if needed
		if (lazy[i] != 0LL) {

			seg[i] += lazy[i];

			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += lazy[i];
				lazy[(2LL * i) + 2LL] += lazy[i];
			}

			lazy[i] = 0LL;
		}

		if ((r_incr < l_range) || (l_incr > r_range) || (l_range > r_range))
			return -1e16;

		if ((l_range >= l_incr) && (r_range <= r_incr)) {
			return seg[i];
		}

		//partial overlap case
		ll mid = l_range + (r_range - l_range) / 2LL;
		ll leftSeg = this->query_maxLazy((2LL * i) + 1LL, l_range, mid, l_incr, r_incr);
		ll rightSeg = this->query_maxLazy((2LL * i) + 2LL, mid + 1LL, r_range, l_incr, r_incr);

		return max(leftSeg , rightSeg);
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

	//increase the value of l to r by val
	void rangeUpdate_min(ll i, ll l_range, ll r_range, ll l_incr, ll r_incr, ll val) {

		//first update the lazy tree if needed
		if (lazy[i] != 0LL) {

			seg[i] += lazy[i];

			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += lazy[i];
				lazy[(2LL * i) + 2LL] += lazy[i];
			}

			lazy[i] = 0LL;
		}

		if ((r_incr < l_range) || (l_incr > r_range) || (l_range > r_range))
			return;

		//if seg tree range completely lies then add value to that node
		//and update values of child nodes of current node (propogate updates)
		if ((l_range >= l_incr) && (r_range <= r_incr)) {
			seg[i] += val;
			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += val;
				lazy[(2LL * i) + 2LL] += val;
			}
			return;
		}

		//partial overlap case
		ll mid = l_range + (r_range - l_range) / 2LL;
		this->rangeUpdate_min((2LL * i) + 1LL, l_range, mid, l_incr, r_incr, val);
		this->rangeUpdate_min((2LL * i) + 2LL, mid + 1LL, r_range, l_incr, r_incr, val);
		seg[i] = min(seg[(2LL * i) + 1LL] , seg[(2LL * i) + 2LL]);
	}

	//use this if you are using rangeUpdate_max
	ll query_minLazy(ll i, ll l_range, ll r_range, ll l_incr, ll r_incr) {

		//first update the lazy tree if needed
		if (lazy[i] != 0LL) {

			seg[i] += lazy[i];

			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += lazy[i];
				lazy[(2LL * i) + 2LL] += lazy[i];
			}

			lazy[i] = 0LL;
		}

		if ((r_incr < l_range) || (l_incr > r_range) || (l_range > r_range))
			return 1e16;

		if ((l_range >= l_incr) && (r_range <= r_incr)) {
			return seg[i];
		}

		//partial overlap case
		ll mid = l_range + (r_range - l_range) / 2LL;
		ll leftSeg = this->query_minLazy((2LL * i) + 1LL, l_range, mid, l_incr, r_incr);
		ll rightSeg = this->query_minLazy((2LL * i) + 2LL, mid + 1LL, r_range, l_incr, r_incr);

		return min(leftSeg , rightSeg);
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

	//increase the value of l to r by val
	void rangeUpdate_sum(ll i, ll l_range, ll r_range, ll l_incr, ll r_incr, ll val) {

		//first update the lazy tree if needed
		if (lazy[i] != 0LL) {

			seg[i] += (r_range - l_range + 1LL) * lazy[i];

			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += lazy[i];
				lazy[(2LL * i) + 2LL] += lazy[i];
			}

			lazy[i] = 0LL;
		}

		if ((r_incr < l_range) || (l_incr > r_range) || (l_range > r_range))
			return;

		//if seg tree range completely lies then add value to that node
		//and update values of child nodes of current node (propogate updates)
		if ((l_range >= l_incr) && (r_range <= r_incr)) {

			seg[i] += (r_range - l_range + 1LL) * val;
			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += val;
				lazy[(2LL * i) + 2LL] += val;
			}
			return;
		}

		//partial overlap case
		ll mid = l_range + (r_range - l_range) / 2LL;
		this->rangeUpdate_sum((2LL * i) + 1LL, l_range, mid, l_incr, r_incr, val);
		this->rangeUpdate_sum((2LL * i) + 2LL, mid + 1LL, r_range, l_incr, r_incr, val);
		seg[i] = seg[(2LL * i) + 1LL] + seg[(2LL * i) + 2LL];
	}

	//use this if you are using rangeUpdate_sum
	ll query_sumLazy(ll i, ll l_range, ll r_range, ll l_incr, ll r_incr) {

		//first update the lazy tree if needed
		if (lazy[i] != 0LL) {

			seg[i] += (r_range - l_range + 1LL) * lazy[i];

			if (l_range != r_range) {
				lazy[(2LL * i) + 1LL] += lazy[i];
				lazy[(2LL * i) + 2LL] += lazy[i];
			}

			lazy[i] = 0LL;
		}

		if ((r_incr < l_range) || (l_incr > r_range) || (l_range > r_range))
			return 0LL;

		if ((l_range >= l_incr) && (r_range <= r_incr)) {
			return seg[i];
		}

		//partial overlap case
		ll mid = l_range + (r_range - l_range) / 2LL;
		ll leftSeg = this->query_sumLazy((2LL * i) + 1LL, l_range, mid, l_incr, r_incr);
		ll rightSeg = this->query_sumLazy((2LL * i) + 2LL, mid + 1LL, r_range, l_incr, r_incr);

		return leftSeg + rightSeg;
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

	sTree->rangeUpdate_sum(0, 0, n - 1, 0, 2, -20);
	sTree->rangeUpdate_sum(0, 0, n - 1, 1, 3, 10);
	while (q--) {
		ll l, r;
		cin >> l >> r;

		//make sure indexing is 0 based
		l--;
		r--;

		//query whichever the way you need
		cout << sTree->query_sumLazy(0, 0, n - 1, l, r) << endl;
	}

	//make sure to clear these
	v.clear();
	seg.clear();
	lazy.clear();
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