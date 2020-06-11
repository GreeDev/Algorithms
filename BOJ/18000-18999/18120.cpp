#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using ld = long double;

using lli = long long int;
using pll = pair<ld, ld>;
#define Fir first
#define Sec second

struct Crop{
    pll pos;
    lli w;
    bool operator<(const Crop& c) const{
        return GetDistSquare() < c.GetDistSquare();
    }

    ld GetDistSquare() const{
        return pos.Fir * pos.Fir + pos.Sec * pos.Sec;
    }
    ld GetDist() const{
        return sqrt(pos.Fir * pos.Fir + pos.Sec * pos.Sec);
    }
} arr[100000];

lli sum[100000];

int main(){
    fastio;

    int n, c;
    cin >> n >> c;

    int i;
    for(i = 0; i < n; i++){
        cin >> arr[i].pos.Fir >> arr[i].pos.Sec >> arr[i].w;
    }

    sort(arr, arr + n);

    sum[0] = arr[0].w;
    for(i = 1; i < n; i++){
        sum[i] = sum[i - 1] + arr[i].w;
    }

    ld mx = 0;
    ld prv = 0;
    for(i = 0; i < n; i++){
        ld r = 1. * sum[i] / (2 * c);
        ld gap = r - arr[i].GetDist();

        if(gap > 0 && mx < prv + sum[i] * gap - c * r * r){
            mx = prv + sum[i] * gap - c * r * r;
        }
        if(i + 1 < n)
            prv += sum[i] * (arr[i + 1].GetDist() - arr[i].GetDist());
    }
    cout << fixed;
    cout.precision(6);
    cout << mx;
    return 0;
}
