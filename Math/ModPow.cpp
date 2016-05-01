ll mod_pow(ll a, int n, int m) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (a * mod_pow((a * a) % m, n >> 1, m)) % m;
    else
        return mod_pow((a * a) % m, n >> 1, m);
}

