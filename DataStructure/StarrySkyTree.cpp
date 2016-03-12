// Verified
// http://code-festival-2015-final-open.contest.atcoder.jp/tasks/codefestival_2015_final_d
// http://judge.u-aizu.ac.jp/onlinejudge/cdescription.jsp?cid=RitsCamp16Day3&pid=F

template<class T>
struct StarrySkyTree {
    using int_type = T;
    vector<T> data;
    vector<T> lazy;
    int N;
    StarrySkyTree(int n) {
        N=1;
        while(N<n) N<<=1;
        data.assign(2*N-1, 0);
        lazy.assign(2*N-1, 0);
    }
    // [a,b)
    void add(int a,int b, int_type val) {
        add(a,b,val,0,0,N);
    }
    int_type get(int a,int b) {
        return get(a,b,0,0,N);
    }

    void add(int a,int b,int_type val, int k,int l,int r) {
        if(r<=a || b<=l) return;
        if(a<=l && r<=b) {
            lazy[k]+=val;
            return;
        }
        add(a,b,val,k*2+1,l,(l+r)/2);
        add(a,b,val,k*2+2,(l+r)/2,r);
        data[k]=max(data[k*2+1]+lazy[k*2+1], data[k*2+2]+lazy[k*2+2]);
    }

    int_type get(int a,int b, int k,int l, int r) {
        if(r<=a || b<=l) return -INF;
        if(a<=l && r<=b) return data[k]+lazy[k];
        auto lval = get(a,b,k*2+1,l,(l+r)/2);
        auto rval = get(a,b,k*2+2,(l+r)/2,r);
        return max(lval, rval)+lazy[k];
    }
};

