//BOJ 10868 최솟값

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)
#define endl '\n'

const int INF = 1e9;

struct IndexTree{
    int n;
    int seg[404040];
    IndexTree(int _n){
        n = 1;
        while(n < _n)
            n <<= 1;

        fill(seg, seg + 404040, INF);
    }

    void Update(int idx, int v){
        for(int i = idx + n - 1; i; i >>= 1)
            seg[i] = min(seg[i], v);
    }
    int Query(int a, int b){
        int ret = INF;
        if(a > b)
            swap(a, b);
        a = n + a - 1;
        b = n + b - 1;
        while(a < b){
            if(a & 1){
                ret = min(ret, seg[a]);
                a++;
            }
            if(!(b & 1)){
                ret = min(ret, seg[b]);
                b--;
            }
            a >>= 1;
            b >>= 1;
        }
        if(a == b)
            ret = min(ret, seg[a]);
        return ret;
    }
};

int main(){
    fastio;

    int n, m;
    cin >> n >> m;
    IndexTree tree(n);
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        tree.Update(i + 1, k);
    }
    while(m--){
        int a, b;
        cin >> a >> b;
        cout << tree.Query(a, b) << endl;
    }

    return 0;
}
