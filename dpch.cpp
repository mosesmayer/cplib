struct line{
	LL m, c;
	line (LL m = 0, LL c = 0): m(m), c(c){}
	LL get(LL x){
		return m * x + c;
	}
};

class ConvexHull{
	public:
	int size;
	line *hull;
	
	ConvexHull(int maxSize){
		hull = new line[++maxSize], size = 0;
	}
	
	bool is_bad(int cur, int prev, int next){
		line c = hull[cur], p = hull[prev], n = hull[next];
		return (c.c - n.c) * (c.m - p.m) <= (p.c - c.c) * (n.m - c.m);
	}
	
	void add_line(LL m, LL c){
		hull[size++] = line(m, c);
		while(size > 2 && is_bad(size - 2, size - 3, size - 1))
			hull[size - 2] = hull[size - 1], size--;
	}
	
	LL query(LL x){
		int l = -1, r = size - 1;
		while(r - l > 1){
			int m = (l + r) / 2;
			//cout << "QUERY " << l << " " << r << " " << m << endl;
			if(hull[m].get(x) <= hull[m + 1].get(x))
				l = m;
			else r = m;
		}
		return hull[r].get(x);
	}
};
