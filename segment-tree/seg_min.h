#include <vector>
#include <limits>
template<class T>
struct segment{
private:
    struct node{
        int l = 0, r = 0;
        T mx = 0;
    };
    vector<node> tr;
    T unity;

public:
    segment(std::vector<T> &a){
    	tr.resize(a.size() << 2);
    	build(1, 1, a.size(), a);
    	unity = std::numeric_limits<T>::max();
    }

    segment(int n){
        tr.resize(n << 2);
        build(1, 1, n);
        unity = std::numeric_limits<T>::max();
    }

private:
    void pushup(int u){
        tr[u].mx = min(tr[u << 1].mx, tr[u << 1 | 1].mx);
    }
    
    void build(int u, int l, int r, std::vector<T> &a){
        if (l == r){
            tr[u] = {l, l, unity};
            return;
        }
        tr[u] = {l, r, unity};
        int mid = l + r >> 1;
        build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void build(int u, int l, int r){
        if (l == r){
            tr[u] = {l, l, unity};
            return;
        }
        tr[u] = {l, r, unity};
        int mid = l + r >> 1;
        build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    void modify(int u, int x, T val){
        if (tr[u].l == tr[u].r && tr[u].l == x){
            tr[u].mx = val;
            return;
        }
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, val);
        else modify(u << 1 | 1, x, val);
        pushup(u);
    }

    T query(int u, int l, int r){
        if (l <= tr[u].l && r >= tr[u].r) return tr[u].mx;
        int mid = tr[u].l + tr[u].r >> 1;
        T res = unity;
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
