const int mxsz = 1e5 + 3;
int in[mxsz], out[mxsz], flat[mxsz], dep[mxsz];
int currtime = 0;

// dfs, then build segtree/data structure on indices based on flatten.
// query for vertex u becomes from in[u] to out[u];
void dfs(int u, int prev){ // call dfs(root, root)
	dep[u] = dep[prev] + 1;
	flat[++currtime] = u;
	in[u] = currtime;
	for (auto v : adj[u]){
		if (v != prev){
			dfs(v,u);
		}
	}
	out[u] = currtime;
}
