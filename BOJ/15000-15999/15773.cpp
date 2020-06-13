#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

struct Ballon{
    lli l, d;
    bool operator<(Ballon bal){
        return (l + d) < (bal.l + bal.d);
    }
} b[250000];

int main(){
    fastio;
    int n;
    cin >> n;
    int i;
    for(i = 0; i < n; i++){
        cin >> b[i].l >> b[i].d;
    }
    sort(b, b + n);
    priority_queue<int> pq;
    lli val = 0;
    for(i = 0; i < n; i++){
        int pt = (pq.empty() ? 0 : pq.top());

        if(val - pt > b[i].l)
            continue;
        if(val > b[i].l){
            if(pt < b[i].d)
                continue;
            else{
                val -= pt;
                pq.pop();
            }
        }
        val += b[i].d;
        pq.push(b[i].d);
    }
    cout << pq.size();
    return 0;
}
