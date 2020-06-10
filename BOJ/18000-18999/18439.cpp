#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)


using ulli = unsigned long long int;

struct Bit{
    ulli* const bits;
    const size_t word;
    const static size_t wordBit = 6;
    const static size_t wordSize = (1ULL << wordBit);
    const static ulli maxBit = ~(0ULL);

    Bit(size_t bitSize = 50000) : bits(new ulli[(bitSize >> wordBit) + 1]), word((bitSize >> wordBit) + 1){
        //cout << "generated : size " << bitSize << '\n';
        fill(bits, bits + word, 0);
    }

    Bit& operator=(Bit& b){
        copy(b.bits, b.bits + word, bits);
        return *this;
    }

    Bit& operator<<=(int sh){
        ulli carry = 0;
        for(int i = 0; i < word; i++){
            ulli temp = carry;
            carry = (bits[i] >> (wordSize - sh));
            bits[i] <<= sh;
            bits[i] |= temp;
        }
        return *this;
    }

    void Oper1(){
        (*this) <<= 1;
        bits[0] |= 1;
    }

    void Oper2(Bit& mbit){
        for(int i = 0; i < word; i++){
            ulli x = bits[i];
            bits[i] = x & (x ^ mbit.bits[i]);
        }
    }

    Bit& operator-=(Bit& m){
        ulli carry = 0;
        for(int i = 0; i < word; i++){
            ulli temp = bits[i];
            carry = ((bits[i] = temp - carry) > temp);
            temp = bits[i];
            carry += ((bits[i] = temp - m.bits[i]) > temp);
        }
        return *this;
    }
    bool operator[](size_t idx){
        return (bits[idx >> wordBit] >> (idx & ((1 << wordBit) - 1))) & 1;
    }
    void SetBit(size_t idx){
        bits[idx >> wordBit] |= (1ULL << (idx & (wordSize - 1)));
    }
    void SaveOr(Bit& a, Bit& b){
        for(int i = 0; i < word; i++){
            bits[i] = a.bits[i] | b.bits[i];
        }
    }

    size_t PopCount(){
        size_t ret = 0;
        for(int i = 0; i < word ; i++){
            ret += __builtin_popcountll(bits[i]);
        }
        return ret;
    }
} match[26];

int main(){
    string a, b;
    cin >> a >> b;
    for(int i = 0; i < b.size(); i++){
        match[b[i] - 'A'].SetBit(i);
    }

    Bit d, nextD, orx;
    for(int i = 0; i < a.size(); i++){
        nextD.SaveOr(d, match[a[i] - 'A']);

        d.Oper1();
        
        orx = nextD;
        orx -= d;

        nextD.Oper2(orx);
        d = nextD;
    }
    cout << d.PopCount() <<'\n';

    return 0;
}