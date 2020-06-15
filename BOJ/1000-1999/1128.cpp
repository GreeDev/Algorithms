#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;
using pll = pair<lli, lli>;
#define Fir first
#define Sec second

struct Thing{
    lli w, c;
    bool operator<(Thing t){
        if(w != t.w) return w > t.w;
        return c > t.c;
    }
} th[50];

pll sum[50];
int n;

lli GetRes(int now, lli w, bool cons){
    if(now == n)
        return 0;
    if(sum[now].Fir <= w)
        return sum[now].Sec;

    if(now && th[now - 1].w == th[now].w && cons)
        return GetRes(now + 1, w, true);

    lli res = 0;
    if(w >= th[now].w)
        res = GetRes(now + 1, w - th[now].w, false) + th[now].c;
    return max(res, GetRes(now + 1, w, true));
}

int main(){
    fastio;
    cin >> n;
    int i;
    for(i = 0; i < n; i++){
        cin >> th[i].w >> th[i].c;
    }
    sort(th, th + n);

    sum[n - 1] = {th[n - 1].w, th[n - 1].c};

    for(i = n - 2; i >= 0; i--){
        sum[i] = {sum[i + 1].Fir + th[i].w, sum[i + 1].Sec + th[i].c};
    }
    lli c;
    cin >> c;
    cout << GetRes(0, c, false);
    return 0;
}
