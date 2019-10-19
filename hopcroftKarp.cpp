struct Edge{
	int u, v;
	Edge() {}
	Edge(int u, int v): u(u), v(v) {}
};
struct HopcroftKarp{
	int nl, nr;
	vector<Edge> E;
	vector<vector<int> > g;
	vector<int> d, aft, bef;
	HopcroftKarp(int nl, int nr): nl(nl),nr(nr),g(nl+1),E(0),aft(nl+1),bef(nr+1),d(nl+1) {}
	void AddEdge(int u, int v){
		E.emplace_back(u, v);
		g[u].emplace_back(E.size() - 1);
	}

	bool bfs(){
		fill(d.begin(), d.end(), -1);
		queue<int> q;
		for (int i = 1; i <= nl; i++){
			if (aft[i] == 0){
				q.push(i);
				d[i] = 0;
			}
		}
		while (!q.empty()){
			int u = q.front(); q.pop();
			for (int k : g[u]){
				int v = bef[E[k].v];
				if (d[v] == -1){
					d[v] = d[u] + 1;
					q.push(v);
					if (v == 0) return 1;
				}
			}
		}
		return 0;
	}

	bool dfs(int u){
		if (u == 0) return 1;
		for (int i : g[u]){
			int nx = bef[E[i].v];
			if (d[nx] == d[u] + 1 && dfs(nx)){
				bef[E[i].v] = u;
				aft[u] = E[i].v;
				return 1;
			}
		}
		d[u] = -1;
		return 0;
	}
	
	int MaxMatching(){
		int tot = 0;
		fill(aft.begin(), aft.end(), 0);
		fill(bef.begin(), bef.end(), 0);
		while (bfs()){
			for (int i = 1; i <= nl; i++)
				if (aft[i] == 0) tot += dfs(i);
		}
		return tot;
	}
};
int main(){
	int n, m, p; cin >> n >> m >> p;
	HopcroftKarp hk(n, m);
	for (int i = 1, u, v; i <= p; i++){
		u = readInt(); v = readInt();
		hk.AddEdge(u, v);
	}
	printf("%d\n", hk.MaxMatching());
}
