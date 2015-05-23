/*
 * 前処理 O(N)
 * クエリ O(1)
 *
 * Verified
 * http://yukicoder.me/problems/184
 */

template<class T,size_t N,T MOD>
struct Combination {
    typedef T int_type;
    vector<int_type> fact,factr,inv;
    Combination() {
        fact.resize(2*N+1);
        factr.resize(2*N+1);
        inv.resize(2*N+1);
        fact[0]=factr[0]=1;
        inv[1]=1;
        for(int i=2;i<=2*N;i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        for(int i=1;i<=2*N;i++) fact[i]=fact[i-1]*i%MOD, factr[i]=factr[i-1]*inv[i]%MOD;
    }

    int_type C(int n, int r) {
        if(r<0 || r>n) return 0;
        return factr[r]*fact[n]%MOD*factr[n-r]%MOD;
    }

    int_type P(int n,int r) {
        if(r<0 || r>n) return 0;
        return fact[n]*factr[n-r]%MOD;
    }

    int_type H(int n, int r) {
        if(n==0 && r==0) return 1;
        return C(n+r-1,r);
    }
};

