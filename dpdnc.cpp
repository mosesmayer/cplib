//O(g n log n)
const LL INF = 1e18;
int n, g; int c[mxsz]; LL dp[803][mxsz]; LL pref[mxsz];

LL cost(int i, int j){ // precompute/get cost efficiently (preferably O(1))
	if (i > j) return 0;
	return 1LL * (j - i + 1) * (pref[j] - pref[i-1]);
}

void calc(int d, int l, int r, int optl, int optr){
	if (l > r) return;
	int md = (l + r) >> 1, opt = -1;
	LL mn = INF;
	for (int p = optl; p <= min(md, optr); p++){
		LL now = dp[d-1][p-1] + cost(p, md);
		if (now < mn) mn = now, opt = p;
	}
	dp[d][md] = mn;
	calc(d, l, md - 1, optl, opt);
	calc(d, md + 1, r, opt, optr);
}

int main(){
	scanf("%d %d",&n, &g);
	for (int i = 1; i <= n; i++){
		scanf("%d", c + i);
		dp[0][i] = INF;
		pref[i] = pref[i-1] + c[i];
	}
	for (int i = 1; i <= g; i++) calc(i, 1, n, 1, n);
	printf("%lld\n",dp[g][n]);
	return 0;
}
