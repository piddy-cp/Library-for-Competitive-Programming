// https://atcoder.jp/contests/abc167/submissions/23869202
// https://atcoder.jp/contests/abl/submissions/23885889

#include <vector>

template<long long MOD> class modint {
private :
    long long val = 0;
public :
    modint(const long long& val_ = 0) : val(val_ % MOD) { if (val < 0) val += MOD; }
    const long long& get() const { return val; }
    modint<MOD> operator+(const modint<MOD>& rhs) const { return modint<MOD>(val + rhs.get()); }
    modint<MOD> operator-(const modint<MOD>& rhs) const { return modint<MOD>(val - rhs.get()); }
    modint<MOD> operator*(const modint<MOD>& rhs) const { return modint<MOD>(val * rhs.get()); }
    modint<MOD>& operator+=(const modint<MOD>& rhs) { return *this = *this + rhs; }
    modint<MOD>& operator-=(const modint<MOD>& rhs) { return *this = *this - rhs; }
    modint<MOD>& operator*=(const modint<MOD>& rhs) { return *this = *this * rhs; }
    modint<MOD>& operator++() { return *this += 1; }
    modint<MOD>& operator--() { return *this -= 1; }
    modint<MOD> operator++(int) { return modint<MOD>(val++); }
    modint<MOD> operator--(int) { return modint<MOD>(val--); }
    modint<MOD> pow(const unsigned long long& n) const {
        if (n == 0) return 1;
        return (*this * *this).pow(n >> 1) * (n & 1 ? *this : 1);
    }
    modint<MOD> inv() const { return pow(MOD - 2); }
    modint<MOD> operator/(const modint<MOD>& rhs) const { return *this * rhs.inv(); }
    modint<MOD>& operator/=(const modint<MOD>& rhs) const { return *this = *this / rhs; }
    bool operator==(const modint<MOD>& rhs) const { return val == rhs.get(); }
    bool operator!=(const modint<MOD>& rhs) const { return val != rhs.get(); }
};

struct MODFACT {
private :
    std::vector<long long> fact, fact_inv;
public :
    template<long long MOD> void build(int N) {
        fact.resize(N + 1); fact[0] = 1;
        for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
        fact_inv.resize(N + 1);
        fact_inv[N] = modint<MOD>(fact[N]).inv().get();
        for (int i = N - 1; i >= 0; i--) fact_inv[i] = fact_inv[i + 1] * (i + 1) % MOD;
    }
    template<long long MOD> modint<MOD> permutation(int n, int k) const {
        return fact[n] * fact_inv[n - k] % MOD;
    }
    template<long long MOD> modint<MOD> combination(int n, int k) const {
        return permutation<MOD>(n, k) * fact_inv[k];
    }
}; MODFACT modfact;