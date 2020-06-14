#include <bits/stdc++.h>

// begin of definition

using namespace std;

using lli = long long int;
using uint = unsigned int;
using ull = unsigned long long int;

using pii = pair<int, int>;
using pll = pair<lli, lli>;
#define Fir first
#define Sec second
#define MKP make_pair

using vi = vector<int>;
using vii = vector<pii>;
#define pb(X) push_back(X)
#define ALL(X) (X.begin()), (X.end())

using tiii = tuple<int, int, int>;

#define FOR(X, START_VALUE, END_VALUE) for(int X = (START_VALUE); X < (END_VALUE); X++)
#define FORQ(X, START_VALUE, END_VALUE) for(int X = (START_VALUE); X <= (END_VALUE); X++)
#define FOR_V(X, START_VALUE, END_VALUE) for(X = (START_VALUE); X < (END_VALUE); X++)
#define FORQ_V(X, START_VALUE, END_VALUE) for(X = (START_VALUE); X <= (END_VALUE); X++)

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

lli Get_ModInverse(lli a, lli mod){
    lli b = mod;
    pll x = {1, 0};
    pll y = {0, 1};
    while(b){
        x = {x.Fir - y.Fir * (a / b), x.Sec - y.Sec * (a / b)};
        a %= b;
        swap(a, b);
        swap(x, y);
    }
    if(a > 1)
        return -1;
    return x.Fir + (x.Fir < 0 ? mod : 0);
}
// end of definition

int main(){
    fastio;

    return 0;
}
