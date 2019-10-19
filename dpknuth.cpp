int a[1005];
int dp[1005][1005], opt[1005][1005];

const int inf = 1e8;
void solve(){
	for (int i = 1; i <= m; i++) cin >> a[i];
	a[0] = 0, a[m+1] = n;
	m += 2;
	for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) dp[i][j] = opt[i][j] = inf;
	for (int i = 0; i < m; i++){ // len = 1
		dp[i][i+1] = 0;
		opt[i][i+1] = i;
	}
	for (int len = 2; len < m; len++){
		for (int l = 0, r = len; r < m; l++, r++){
			int &mn = dp[l][r];
			for (int k = max(l, opt[l][r-1]); k <= min(r-1, opt[l+1][r]); k++){
				int now = dp[l][k] + dp[k][r] + a[r] - a[l];
				if (now <= mn)
					mn = now, opt[l][r] = k;
			}
		}
	}
	cout << dp[0][m-1] << '\n';
}
