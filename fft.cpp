typedef complex<double> cmplx;

#define FOR(i,a,b) for (int i=a;i<b;i++)
#define fi first
#define se second
#define pb push_back

const double PI = acos(-1.0);

typedef complex<long double> Cld;
// vector<Cld> res;

void FFT(vector<Cld>& a, int sign = 1) {
    int n = a.size(); // n should be a power of two
    double theta = sign * 2 * PI / n;
    for(int i = 0, j = 1; j < n - 1; ++j) {
       for(int k = n >> 1; k > (i ^= k); k >>= 1);
       if(j < i) swap(a[i], a[j]);
    }
    for(int m, mh = 1; (m = mh << 1) <= n; mh = m) {
        int irev = 0;
        for(int i = 0; i < n; i += m) {
            Cld  w = exp(Cld(0, theta*irev));
            for(int k = n >> 2; k > (irev ^= k); k >>= 1);
            for(int j = i; j < mh + i; ++j) {
                int k = j + mh;
                Cld x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
    }
    if(sign == -1) FOR(i,0,n)a[i] /= n;
}

void vector_multiply(vector<Cld>& res, vector<Cld>& a, vector<Cld>& b){ // multiplies, stores to a
    res.clear();
    int n = a.size() + b.size() - 1;
    for(int i=1; i<n; i<<=1)if(n&i)n += i;
    a.resize(n);
    b.resize(n);

    FFT(a);
    FFT(b);
    FOR(i,0,n)res.pb(a[i] * b[i]);
    FFT(res, -1);
    FOR(i,0,n) res[i] = Cld((int(res[i].real()+0.5))%1009); // specific to lightsabers
}
