#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

struct BigInt{
    static const lli mod = 1e9;

    vector<lli> num;

    BigInt() : num(1){}

    BigInt& operator*=(int x){
        for(int i = 0; i < num.size(); i++){
            num[i] *= x;
        }
        for(int i = 0; i < num.size(); i++){
            if(num[i] >= mod){
                if(i + 1 == num.size())
                    num.push_back(0);
                num[i + 1] += num[i] / mod;
                num[i] %= mod;
            }
        }
        return *this;
    }
    BigInt operator*(int x){
        BigInt res;
        res += *this;
        res *= x;
        return res;
    }
    BigInt& operator+=(BigInt x){
        if(num.size() < x.num.size())
            num.resize(x.num.size());
        for(int i = 0; i < x.num.size(); i++){
            num[i] += x.num[i];
        }
        for(int i = 0; i < num.size(); i++){
            if(num[i] >= mod){
                if(i + 1 == num.size())
                    num.push_back(0);
                num[i + 1] += num[i] / mod;
                num[i] %= mod;
            }
        }
        return *this;
    }

    BigInt& operator+=(int x){
        num[0] += x;
        for(int i = 0; i < num.size(); i++){
            if(num[i] >= mod){
                if(i + 1 == num.size())
                    num.push_back(0);
                num[i + 1] += num[i] / mod;
                num[i] %= mod;
            }
            else break;
        }
        return *this;
    }
    BigInt& operator-=(BigInt x){
        for(int i = 0; i < x.num.size(); i++){
            num[i] -= x.num[i];
        }
        for(int i = 0; i < num.size(); i++){
            if(num[i] < 0){
                num[i] += mod;
                num[i + 1]--;
            }
        }
        while(num.size() > 1 && num.back() == 0)
            num.pop_back();
        return *this;
    }
    BigInt& operator/=(int d){
        for(int i = 0; i < num.size(); i++){
            if(i) num[i - 1] += (num[i] % d) * (mod / 10);
            num[i] /= d;
        }
        while(num.size() > 1 && num.back() == 0)
            num.pop_back();
        return *this;
    }
    BigInt& Divide(BigInt d, BigInt& result){
        BigInt add;
        add.num[0] = 1;
        int i = 0;
        while(d <= *this){
            add *= 10;
            d *= 10;
            i++;
        }
        d /= 10;
        add /= 10;
        while(i--){
            while(d <= *this){
                result += add;
                *this -= d;
            }
            d /= 10;
            add /= 10;
        }
        return *this;
    }
    bool operator<(BigInt b){
        if(num.size() != b.num.size())
            return num.size() < b.num.size();
        for(int i = num.size() - 1; i >= 0; i--){
            if(num[i] != b.num[i])
                return num[i] < b.num[i];
        }
        return false;
    }
    bool operator<=(BigInt b){
        if(num.size() != b.num.size())
            return num.size() < b.num.size();
        for(int i = num.size() - 1; i >= 0; i--){
            if(num[i] != b.num[i])
                return num[i] < b.num[i];
        }
        return true;
    }

    void Print(){
        for(int i = num.size() - 1; i >= 0; i--){
            if(i != num.size() - 1){
                cout.width(9);
                cout.fill('0');
            }
            cout << num[i];
        }
        cout.width(0);
        cout.fill(' ');
    }
};

int main()
{
    fastio;
    BigInt a, b;
    string s;
    cin >> s;
    for(char c : s){
        a *= 10;
        a += (c - '0');
    }
    cin >> s;
    for(char c : s){
        b *= 10;
        b += (c - '0');
    }
    BigInt res;
    a.Divide(b, res);

    res.Print();
    cout << '\n';
    a.Print();
    return 0;
}
