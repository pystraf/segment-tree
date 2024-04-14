#include<vector>
template<class T>
struct segment{
private:
    struct node{
        int l = 0, r = 0;
        T sum = 0;
    };
    vector<node> tr;

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
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }
    
    void build(int u, int l, int r, std::vector<T> &a){
        if (l == r){
            tr[u] = {l, l, a[l - 1]};
            return;
        }
        tr[u] = {l, r, 0};
        int mid = l + r >> 1;
        build(u << 1, l, mid, a); build(u << 1 | 1, mid + 1, r, a);
        pushup(u);
    }

    void build(int u, int l, int r){
        if (l == r){
            tr[u] = {l, l, 0};
            return;
        }
        tr[u] = {l, r, 0};
        int mid = l + r >> 1;
        build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void modify(int u, int x, T val){
        if (tr[u].l == tr[u].r && tr[u].l == x){
            tr[u].sum = val;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, val);
        else modify(u << 1 | 1, x, val);
        pushup(u);
    }

    T query(int u, int l, int r){
        if (l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
        int mid = tr[u].l + tr[u].r >> 1;
        T res{};
        if (l <= mid) res = query(u << 1, l, r);
        if (r > mid) res = max(res, query(u << 1 | 1, l, r));
        return res;
    }

public:
	void modify(int x, T v){
		modify(1, x, v);
	}
	
	T query(int l, int r){
		return query(1, l, r);
	}
};
