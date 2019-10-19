void getSz(int x, int p = -1){
    sz[x] = 1;
    for(int i = 0; i < adj[x].size(); ++i){
        int nx = adj[x][i].fi;
        if(nx == p || isCentroid[nx])continue;
        getSz(nx, x);
        sz[x] += sz[nx];
    }
}
int getCentroid(int x, int p, int totSz){
    for(int i = 0; i < adj[x].size(); ++i){
        int nx = adj[x][i].fi;
        if(nx == p || isCentroid[nx])continue;
        if(sz[nx] > totSz / 2)return getCentroid(nx, x, totSz);
    }
    return x;
}
int buildCentroid(int x, int p = -1){
    getSz(x, p);
    int cen = getCentroid(x, p, sz[x]);
    par[cen] = p;
    isCentroid[cen] = true;
    for(int i = 0; i < adj[cen].size(); ++i){
        int nx = adj[cen][i].fi;
        if(nx == p || isCentroid[nx])continue;
        tree[cen].pb(buildCentroid(nx, cen));
    }
    return cen;
}