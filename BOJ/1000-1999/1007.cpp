#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

using pll = pair<lli, lli>;
#define Fir first
#define Sec second

pll pos[20];
int n;

pll operator+(pll a, pll b){
    return {a.Fir + b.Fir, a.Sec + b.Sec};
}
pll operator-(pll a, pll b){
    return {a.Fir - b.Fir, a.Sec - b.Sec};
}

double GetRes(int now, int pick, pll sum){
    if(now == n){
        return sqrt((double)sum.Fir * sum.Fir + sum.Sec * sum.Sec);
    }
    if(pick == 0)
        return GetRes(now + 1, 0, sum - pos[now]);
    if(pick == n - now)
        return GetRes(now + 1, pick - 1, sum + pos[now]);
    return min(GetRes(now + 1, pick, sum - pos[now]), GetRes(now + 1, pick - 1, sum + pos[now]));
}

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        cin >> n;
        int i;
        for(i = 0; i < n; i++){
            cin >> pos[i].Fir >> pos[i].Sec;
        }
        cout << fixed;
        cout.precision(6);
        cout << GetRes(0, n / 2, {0, 0}) << '\n';
    }
    return 0;
}
