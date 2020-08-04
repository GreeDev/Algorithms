//BOJ 18440 LCS 7

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)


class BitMaster{

using ulli = unsigned long long int;

private:
    ulli* bits = nullptr;
    size_t _size, bck;
public:
    BitMaster(const BitMaster& src) : bits(new ulli[src._size / 64 + 1]), _size(src._size), bck(src._size / 64 + 1){
        copy(src.bits, src.bits + (_size / 64 + 1), bits);
    }
    BitMaster(unsigned int _sz = 50002) : bits(new ulli[_sz / 64 + 1]), _size(_sz), bck(_sz / 64 + 1){
        fill(bits, bits + bck, 0);
    }
    ~BitMaster(){
        delete[] bits;
    }

    void clear(){
        fill(bits, bits + bck, 0);
    }
    size_t size(){
        return _size;
    }

    bool operator[](int idx){
        return (bits[idx / 64] >> (idx % 64)) & 1;
    }

    BitMaster& Set(int idx, ulli b = 1){
        bits[idx / 64] |= (1LL << (idx % 64));
        return *this;
    }

    BitMaster& operator=(const BitMaster& src){
        _size = src._size;
        copy(src.bits, src.bits + bck, bits);
        return (*this);
    }

    size_t PopCount(){
        size_t sz = 0;
        for(size_t i = 0; i <= bck; i++)
            sz += __builtin_popcountll(bits[i]);
        return sz;
    }
    BitMaster& FastQuery(const BitMaster& mat, const BitMaster& op){
        ulli m_carry = 0, sh_carry = 1;
        for(size_t i = 0; i <= bck; i++){
            bits[i] = mat.bits[i] | op.bits[i];

            ulli now_bit = bits[i];

            ulli opb = (op.bits[i] << 1) | sh_carry;
            sh_carry = (op.bits[i] >> 63);
            ulli temp = now_bit;
            m_carry = (now_bit -= m_carry) > temp;
            temp = now_bit;
            m_carry += (now_bit -= opb) > temp;
            bits[i] = bits[i] & (bits[i] ^ now_bit);
        }
        return *this;
    }
};

string a, b;

BitMaster lcs_r, rev_lcs_r;

BitMaster x;
int LCS(int ax, int ay, int bx, int by){
    BitMaster match[26];
    lcs_r.clear();
    for(int i = bx; i <= by; i++){
        match[b[i] - 'A'].Set(i - bx);
    }
    for(int i = ax; i <= ay; i++){
        lcs_r = x.FastQuery(match[a[i] - 'A'], lcs_r);
    }
    return lcs_r.PopCount();
}
int ReverseLCS(int ax, int ay, int bx, int by){
    BitMaster match[26];
    rev_lcs_r.clear();
    for(int i = by; i >= bx; i--){
        match[b[i] - 'A'].Set(by - i);
    }
    for(int i = ay; i >= ax; i--){
        rev_lcs_r = x.FastQuery(match[a[i] - 'A'], rev_lcs_r);
    }
    return rev_lcs_r.PopCount();
}

int lv[50002], rv[50002];

void Hirschberg(int ax, int ay, int bx, int by, int ans){
    if(ans == by - bx + 1){
        for(int i = bx; i <= by; i++)
            cout << b[i];
        return;
    }
    if(ans == ay - ax + 1){
        for(int i = ax; i <= ay; i++)
            cout << a[i];
        return;
    }
    int aMid = (ax + ay) / 2;

    int lans = LCS(ax, aMid, bx, by);
    int rans = ReverseLCS(aMid + 1, ay, bx, by);

    if(ans == lans){
        Hirschberg(ax, aMid, bx, by, ans);
        return;
    }
    if(ans == rans){
        Hirschberg(aMid + 1, ay, bx, by, ans);
        return;
    }

    int tail = by - bx + 1;

    for(int i = 1; i <= tail; i++){
        lv[i] = lv[i - 1] + lcs_r[i - 1];
        rv[i] = rv[i - 1] + rev_lcs_r[i - 1];
    }

    int lm = 0, rm = 0;
    int idx = 0;
    for(int i = 0; i <= tail; i++){
        if(lv[i] + rv[tail - i] == ans){
            lm = lv[i];
            rm = rv[tail - i];
            idx = i;
            break;
        }
    }
    if(lm) Hirschberg(ax, aMid, bx, bx + idx - 1, lm);
    if(rm) Hirschberg(aMid + 1, ay, bx + idx, by, rm);
}

int main(){
    fastio;
    cin >> a >> b;

    int r = LCS(0, a.size() - 1, 0, b.size() - 1);
    cout << r << '\n';
    if(r) Hirschberg(0, a.size() - 1, 0, b.size() - 1, r);
}
