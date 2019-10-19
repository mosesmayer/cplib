#include <random>
#include <chrono>
using namespace std;
typedef long long LL;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); // set seed
struct node{
	LL prior; int sz, val;
	bool lz;
	node *l, *r;
	node(int v=0): prior(rnd()), size(1), lz(0),val(v), l(NULL), r(NULL){
	}
};
typedef node* pnode;

struct Treap{
	pnode root;
	Treap(){ root = nullptr;}
	inline int getsz(pnode t){
		return t ? t -> size : 0;
	}
	void upd_sz(pnode t){ // merge operation
		if (t){
			t -> size = getsz(t -> l) + 1 + getsz(t->r);
			//begin operation - change according to q
			for (int i = 1; i <= 26; i++){
				t -> cnt[i] = 0;
				if (t -> l) t->cnt[i] += t->l->cnt[i];
				if (t -> r) t->cnt[i] += t->r->cnt[i];
			}
			t->cnt[t->val]++;
			//end operation
		}
	}

	void prop(pnode t){
		if (!t) return;
		if (t -> lz){
			swap(t -> l, t -> r);
			if (t -> l) t->l->lz ^= 1;
			if (t -> r) t->r->lz ^= 1;
		}
		t->lz = 0;
		upd_sz(t);
	}

	void split(pnode t, pnode &l, pnode &r, int x, int add = 0){
		if (!t) return void(l = r = NULL);
		prop(t);
		int cur_key = add + getsz(t->l);
		if (cur_key <= x) split(t->r, t->r, r, x, cur_key+1), l = t;
		else split(t->l, l, t->l, x, add), r = t;
		upd_sz(t);
	}

	void merge(pnode &t, pnode l, pnode r){
		prop(l); prop(r);
		if (!l || !r){t = l ? l : r;}
		else if (l -> prior > r -> prior) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;
		upd_sz(t);
	}

	void rev(pnode t, int l, int r){ // split to left l, then right r, then swap
		pnode a, b, c;
		split(t, b, c, r);
		split(b, a, b, l-1);
		b -> lz ^= 1;
		merge(b, a, b);
		merge(t, b, c);
	}

}
