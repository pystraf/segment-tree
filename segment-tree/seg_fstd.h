#include <vector>
template<class T>
struct segment{
private:
	struct node{
		int l, r;
		T lazy, sum1, sum2;
	};
	std::vector<node> tr;
public:
	segment(std::vector<T> &a){
		tr.resize(a.size() << 2);
		build(1, 1, a.size(), a);
	}

	segment(int n){
		tr.resize(n << 2);
		build(1, 1, n);
	}

private:
	void pushup(int u){
		tr[u].sum1 = tr[u << 1].sum1 + tr[u << 1 | 1].sum1;
		tr[u].sum2 = tr[u << 1].sum2 + tr[u << 1 | 1].sum2;
	}
	
	void pushdown(int u){
		if(tr[u].lazy){
			tr[u << 1].sum2 += (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].lazy * tr[u].lazy + 2 * tr[u].lazy * tr[u << 1].sum1;
			tr[u << 1 | 1].sum2 += (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].lazy * tr[u].lazy + 2 * tr[u].lazy * tr[u << 1 | 1].sum1;
			tr[u << 1].sum1 += (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].lazy;
			tr[u << 1 | 1].sum1 += (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].lazy;
			tr[u << 1].lazy += tr[u].lazy;
			tr[u << 1 | 1].lazy += tr[u].lazy;
			tr[u].lazy = 0;
		}
	}
	
	void build(int u, int l, int r, std::vector<T> &a){
		tr[u] = {l, r};
		if(l == r){
			tr[u].sum1 = a[l - 1];
			tr[u].sum2 = a[l - 1] * a[l - 1];
			return;
		}
		int mid = l + r >> 1;
		build(u << 1, l, mid, a);
		build(u << 1 | 1, mid + 1, r, a);
		pushup(u);
	}

	void build(int u, int l, int r){
		tr[u] = {l, r};
		if(l == r){
			tr[u].sum1 = 0;
			tr[u].sum2 = 0;
			return;
		}
		int mid = l + r >> 1;
		build(u << 1, l, mid, a);
		build(u << 1 | 1, mid + 1, r, a);
		pushup(u);
	}
	
	void modify(int u, int l, int r, T v){
		if(tr[u].l >= l && tr[u].r <= r){
			tr[u].sum2 += (tr[u].r - tr[u].l + 1) * v * v + 2 * v * tr[u].sum1;
			tr[u].sum1 += (tr[u].r - tr[u].l + 1) * v;
			tr[u].lazy += v;
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if(l <= mid) modify(u << 1, l, r, v);
		if(r > mid) modify(u << 1 | 1, l, r, v);
		pushup(u);
	}
	
	T query(int u, int l, int r){
		if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum1;
		pushdown(u);
		T res = 0;
		int mid = tr[u].l + tr[u].r >> 1;
		if(l <= mid) res += query(u << 1, l, r);
		if(r > mid) res += query(u << 1 | 1, l, r);
		return res;
	}
	
	T query2(int u, int l, int r){
		if(tr[u].l >= l && tr[u].r <= r) return tr[u].sum2;
		pushdown(u);
		T res = 0;
		int mid = tr[u].l + tr[u].r >> 1;
		if(l <= mid) res += query2(u << 1, l, r);
		if(r > mid) res += query2(u << 1 | 1, l, r);
		return res;
	}
public:
	void modify(int l, int r, T v){
		modify(1, l, r, v);
	}
	
	T query(int l, int r){
		int len = r - l + 1;
		T f = query(1, l, r) / len;
		update(l, r, -f);
		T res = query2(1, l, r) / len;
		update(l, r, f);
		return res;
	}
};
