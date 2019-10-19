int AM[mxsz][mxsz]; // adjacency matrix
LL dist[mxsz][mxsz];
void floydWarshall(){ // O(n^3)
	//init all non-adjacent distances to INF else ADM[i][j]
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
