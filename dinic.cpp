struct Edge{
	int u, v;
	LL cap, flow;
	Edge(int u=0, int v=0, LL cap=0): u(u), v(v), cap(cap), flow(0) {}
};
struct Dinic{
	int n;
	vector<Edge> E;
	vector<vi> g;
	vi d, pt;
	
	Dinic(int n): n(n), E(0), g(n), d(n), pt(n) {}
	void addEdge(int u, int v, LL cap){
		if (u == v) return;
		E.eb(u, v, cap);
		g[u].eb(E.size() - 1);
		E.eb(v,u,0);
		g[v].eb(E.size() - 1);
	}
	bool bfs(int s, int t){
		queue<int> q; q.push(s);
		fill(d.begin(), d.end(), n+1);
		d[s] = 0;
		while (!q.empty()){
			int u = q.front(); q.pop();
			if (u == t) break;
			for (int k : g[u]){
				Edge &e = E[k];
				if (e.flow < e.cap && d[e.v] > d[e.u] + 1){
					d[e.v] = d[e.u] + 1;
					q.push(e.v);
				}
			}
		}
		return d[t] != n+1;
	}
	LL dfs(int u, int t, LL flow = -1){
		if (u == t || flow == 0) return flow;
		for (int &i = pt[u]; i < g[u].size(); i++){
			Edge &e = E[g[u][i]];
			Edge &oe = E[g[u][i]^1];
			if (d[e.v] == d[e.u] + 1){
				LL amt = e.cap - e.flow;
				if (flow != -1 && amt > flow) amt = flow;
				if (LL pushed = dfs(e.v, t, amt)){
					e.flow += pushed; oe.flow -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}
	LL maxFlow(int s, int t){
		LL tot = 0LL;
		while (bfs(s, t)){
			fill(pt.begin(), pt.end(), 0);
			while (LL flow = dfs(s, t)) tot += flow;
		}
		return tot;
	}
};

