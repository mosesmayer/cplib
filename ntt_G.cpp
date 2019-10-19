const int mxsz = 4e6 + 5; // mxs*mxd
const LL mod = 998244353;
int n, k;
int d[15];
LL arr[mxsz], r[mxsz];

LL fpow(LL b, LL e){
	LL ret = 1LL;
	for (;e > 0; e>>=1){
		if (e & 1){ret *= b;ret %= mod;}
		b *= b; b %= mod;
	}
	return ret;
}

void ntt(LL *a, int N, int root){
	for (int i = 0; i < N; i++)
		if (i < r[i]) swap(a[i], a[r[i]]);
	for (int i = 1; i < N; i<<=1){
		int r = fpow(root, (mod-1)/(i<<1));
		for (int j = 0; j < N; j += (i<<1)){
			for (int k = 0, t = 1; k < i; k++, t = (t*r)%mod){
				int x1 = a[j+k], x2 = (a[i+j+k] * t) % mod;
				a[j+k] = (x1 + x2) % mod;
				a[i+j+k] = (x1 + mod - x2) % mod;
			}
		}
	}
}
int32_t main(){
	cin >> n >> k;
	LL mx = 0;
	FOR(i,0,k){
		cin >> d[i];
		mx = max(mx, d[i]);
		arr[d[i]] = 1;
	}
	n /= 2;
	int N = 1, sh = -1;
	while (N <= (n*10)){
		N <<= 1; sh++;}
	for (int i = 0; i < N; i++)
		r[i] = (r[i>>1]>>1) | ((i & 1) << sh);
	ntt(arr,N,3);
	for (int i = 0; i < N; i++)
		arr[i] = fpow(arr[i], n);
	ntt(arr, N, (mod+1)/3);
	int inv = fpow(N, mod-2); LL ans = 0;
	for (int i = 0; i < N; i++) arr[i] = (arr[i] * inv) % mod;
	for (int i = 0; i < N; i++){
		ans += (arr[i] * arr[i]) % mod;
		ans %= mod;
	}
	cout << ans << '\n';
	return 0;
}
