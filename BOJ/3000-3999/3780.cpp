#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using pii = pair<int, int>;
#define Fir first
#define Sec second

int line[20001];

int root[20001];

pii GetRoot(int x){
    if(x == root[x])
        return pii(x, line[x]);

    pii rt = GetRoot(root[x]);
    root[x] = rt.Fir;
    line[x] += rt.Sec;
    return {rt.Fir, line[x]};
}

void Union(int a, int b){
    int aRoot = GetRoot(a).Fir;
    int bRoot = GetRoot(b).Fir;
    if(aRoot == bRoot)
        return;
    line[aRoot] = abs(b - a) % 1000;
    root[aRoot] = b;
}

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            root[i] = i;
        fill(line, line + 20001, 0);
        while(true){
            char cmd;
            int v;
            cin >> cmd;
            if(cmd == 'O')
                break;
            if(cmd == 'I'){
                int a, b;
                cin >> a >> b;
                Union(a, b);
            }
            if(cmd == 'E'){
                int v;
                cin >> v;
                GetRoot(v);
                cout << line[v] << '\n';
            }
        }
    }
    return 0;
}
