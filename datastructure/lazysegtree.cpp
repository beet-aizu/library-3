template <class M>
struct LazySegmentTree{
    using T = typename M::T;
    using L = typename M::L;
    int sz, n, height{};
    vector<T> seg; vector<L> lazy;
    explicit LazySegmentTree(int n) : n(n) {
        sz = 1; while(sz < n) sz <<= 1, height++;
        seg.assign(2*sz, M::e());
        lazy.assign(2*sz, M::l());
    }

    void set(int k, const T &x){ seg[k + sz] = x; }

    void build(){
        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);
    }

    T reflect(int k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k], lazy[k]); }

    void eval(int k){
        if(lazy[k] == M::l()) return;
        if(k < sz){
            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);
            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);
        }
        seg[k] = reflect(k);
        lazy[k] = M::l();
    }
    void thrust(int k){ for (int i = height; i; --i) eval(k>>i); }
    void recalc(int k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}

    void update(int a, const T &x){
        thrust(a += sz);
        seg[a] = x;
        recalc(a);
    }

    void update(int a, int b, const L &x){
        thrust(a += sz); thrust(b += sz-1);
        for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {
            if(l&1) lazy[l] = M::h(lazy[l], x), l++;
            if(r&1) --r, lazy[r] = M::h(lazy[r], x);
        }
        recalc(a);
        recalc(b);
    }

    T query(int a, int b){ // [l, r)
        thrust(a += sz);
        thrust(b += sz-1);
        T ll = M::e(), rr = M::e();
        for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {
            if (l & 1) ll = M::f(ll, reflect(l++));
            if (r & 1) rr = M::f(reflect(--r), rr);
        }
        return M::f(ll, rr);
    }

    template<class F>
    int search_right(int l, F cond){
        if(l == n) return n;
        thrust(l += sz);
        T val = M::e();
        do {
            while(!(l&1)) l >>= 1;
            if(!cond(M::f(val, seg[l]))){
                while(l < sz) {
                    eval(l); l <<= 1;
                    if (cond(M::f(val, reflect(l)))){
                        val = M::f(val, reflect(l++));
                    }
                }
                return l - sz;
            }
            val = M::f(val, reflect(l++));
        } while((l & -l) != l);
        return n;
    }

    template<class F>
    int search_left(int r, F cond){
        if(r <= 0) return 0;
        thrust((r += sz)-1);
        T val = M::e();
        do {
            r--;
            while(r > 1 && r&1) r >>= 1;
            if(!cond(M::f(reflect(r), val))){
                while(r < sz) {
                    eval(r);
                    r = ((r << 1)|1);
                    if (cond(M::f(reflect(r), val))){
                        val = M::f(reflect(r--), val);
                    }
                }
                return r + 1 - sz;
            }
            val = M::f(reflect(r), val);
        } while((r & -r) != r);
        return 0;
    }
};

/*
struct Monoid{
    using T = array<mint, 2>;
    using L = array<mint, 2>;
    static T f(T a, T b) { return {a[0]+b[0], a[1]+b[1]}; }
    static T g(T a, L b) {
        return {a[0] * b[0] + a[1] * b[1], a[1]};
    }
    static L h(L a, L b) {
        return {a[0]*b[0], a[1]*b[0]+b[1]};
    }
    static T e() { return {0, 0}; }
    static L l() { return {1, 0}; }
};
*/