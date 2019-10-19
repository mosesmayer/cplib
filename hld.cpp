vi adj[mxsz];
int dep[mxsz], in[mxsz], out[mxsz], flat[mxsz];
int sz[mxsz], bc[mxsz], hdchn[mxsz], par[mxsz];

void get_sz(int u, int prv = -1){
    sz[u] = 1;
    for (int nx : adj[u]){
        if (nx == prv) continue;
        dep[nx] = dep[u] + 1;
        get_sz(nx, u); sz[u] += sz[nx];
        if (!bc[u] || sz[nx] > sz[bc[u]]) bc[u] = nx;
    }
    for (int i = 0; i < adj[u].size(); i++)
        if (adj[u][i] == bc[u]){swap(adj[u][0], adj[u][i]);break;}
}
void dfs_hld(int u, int prv, int head){
    static int tme = 0;
    in[u] = ++tme; flat[tme] = u; par[u] = prv;
    hdchn[u] = head;
    if (bc[u]) dfs_hld(bc[u], u, head);
    for (int nx : adj[u]){
        if (nx == prv || nx == bc[u]) continue;
        dfs_hld(nx, u, nx);
    }
    out[u] = tme; // combine euler tree and hld
}
struct SegmentTree{
    LL st[mxsz << 2], lz[mxsz << 2];
	void build(int p = 1, int l = 1, int r = N){
		if (l == r) return void(st[p] = A[flat[l]]);
		int md = (l + r) >> 1;
		build(p<<1, l, md); build(p<<1|1, md+1, r);
		st[p] = st[p<<1] + st[p<<1|1];
	}
} seg;

void upd_sub(int x, LL v){
    seg.upd(in[x], out[x], v);
}
void upd_hld(int x, int y, LL v){
	while (hdchn[x] != hdchn[y]){
		if (dep[hdchn[x]] < dep[hdchn[y]]) swap(x, y);
		seg.upd(in[hdchn[x]], in[x], v);
		x = hdchn[x];
		if (par[x] != -1) x = par[x];
	}
	if (in[x] > in[y]) swap(x, y);
	seg.upd(in[x], in[y], v);
}
LL query_sub(int x){
	return seg.query(in[x], out[x]);
}
LL query_hld(int x, int y){
    LL ret = 0;
    while (hdchn[x] != hdchn[y]){
        if (dep[hdchn[x]] < dep[hdchn[y]]) swap(x, y);
        ret += seg.query(in[hdchn[x]], in[x]);
        x = hdchn[x];
        if (par[x] != -1) x = par[x];
    }
    if (in[x] > in[y]) swap(x, y);
    ret += seg.query(in[x], in[y]);
    return ret;
}
int main(){ get_sz(1); dfs_hld(1, -1, 1); seg.build(); }
