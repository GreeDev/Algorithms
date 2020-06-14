#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;
using pll = pair<lli, lli>;
#define Fir first
#define Sec second

pll p[200000];

int main(){
    fastio;
    int n;
    cin >> n;
    int i;
    for(i = 0; i < n; i++){
        cin >> p[i].Sec;
    }
    for(i = 0; i < n; i++){
        cin >> p[i].Fir;
    }
    sort(p, p + n, greater<>());

    priority_queue<lli, vector<lli>, greater<lli>> pq;

    int used = 0;
    for(int i = 0; i < n; i++){
        lli pt = (pq.empty() ? 1e9 : pq.top());
        if(used == pq.size()){
            if(pt < p[i].Sec){
                pq.pop();
                pq.push(p[i].Sec);
            }
            used++;
        }
        else{
            pq.push(p[i].Sec);
        }
    }
    lli res = 0;
    while(!pq.empty())
        res += pq.top(), pq.pop();
    cout << res;
    return 0;
}
