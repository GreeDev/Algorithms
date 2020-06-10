#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

#define SQRT 1000

int arr[1000000];
int srt[1000000];

struct Query{
    int lef, rig;
    int idx;

    bool operator<(Query q){
        if(lef / SQRT != q.lef / SQRT)
            return lef < q.lef;
        return rig < q.rig;
    }
} q[1000000];

int ct[1000000];
int res = 0;
void Add(int i){
    if(!ct[arr[i]])
        res++;
    ct[arr[i]]++;
}
void Erase(int i){
    ct[arr[i]]--;
    if(!ct[arr[i]])
        res--;
}

int r[1000000];

int main(){
    fastio;
    int n;
    cin >> n;
    int i;
    for(i = 0; i < n; i++){
        cin >> arr[i];
        srt[i] = arr[i];
    }
    sort(srt, srt + n);
    for(i = 0; i < n; i++){
        arr[i] = lower_bound(srt, srt + n, arr[i]) - srt;
    }

    int m;
    cin >> m;
    for(i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;b--;
        q[i] = {a, b, i};
    }
    sort(q, q + m);

    int lo = 0, hi = 0;
    Add(0);
    for(i = 0; i < m; i++){
        while(hi < q[i].rig) Add(++hi);
        while(q[i].lef < lo) Add(--lo);
        while(q[i].rig < hi) Erase(hi--);
        while(lo < q[i].lef) Erase(lo++);

        r[q[i].idx] = res;
    }
    for(i = 0; i < m; i++){
        cout << r[i] << '\n';
    }
    return 0;
}
