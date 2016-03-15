// Verified
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
//


template<class T>
struct SegTree {
    typedef T int_type;
    static const size_t MAX_N = 1 << 17;
    static const int_type INIT_VAL = (int_type(1)<<31)-1;
    int_type data[2 * MAX_N - 1];
    size_t n;
    SegTree(size_t n__) {
        n=1;
        while(n < n__) n*=2;
        rep(i,2*n-1) data[i]=INIT_VAL;
    }
    void update(size_t k,int_type a) {
        k+=n-1;
        data[k]=a;
        while(k>0) {
            k=(k-1)/2;
            data[k]=min(data[k*2+1],data[k*2+2]);
        }
    }

    int_type query(size_t a,size_t b,size_t k,size_t l,size_t r) {
        if(r<=a || b<=l) return INIT_VAL;
        if(a<=l && r<=b) return data[k];
        else {
            int_type vl = query(a,b,k*2+1,l,(l+r)/2);
            int_type vr = query(a,b,k*2+2,(l+r)/2,r);
            return min(vl,vr);
        }
    }
    int_type query(size_t a,size_t b) {
        return query(a,b,0,0,n);
    }
};

