struct edge{
	int v; LL w;
	edge(int v = 0, LL w = 0): v(v), w(w){}
};
struct dijkstracmp{
	bool operator() (const edge &lhs, const edge &rhs){
		return lhs.w > rhs.w;
	}
};
const LL INF = 1e15;
vector<edge> adj[mxsz];
LL dist[mxsz];
void getinput(); // add two-way edges
priority_queue<edge, vector<edge>, dijkstracmp> pq;
void dijkstra(int st){
	for (int i = 1; i <= n; i++) dist[i] = INF;
	dist[st] = 0;
	pq.push(edge(st, 0));
	while (!pq.empty()){
		edge u = pq.top(); pq.pop();
		if (dist[u.v] < u.w) continue;
		for (auto v : adj[u.v]){
			if (dist[v.v] > dist[u.v] + v.w){
				dist[v.v] = dist[u.v] + v.w;
				pq.push(edge(v.v, dist[v.v]));
			}
		}
	}
}
int main(){ getinput(); dijkstra(); return 0; }
