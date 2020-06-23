#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using pii = pair<int, int>;
#define Fir first
#define Sec second

int root[100001];
int w[100001];
pii GetRoot(int x){
    if(root[x] == x)
        return {x, 0};

    pii rt = GetRoot(root[x]);
    w[x] += rt.Sec;
    root[x] = rt.Fir;
    return {rt.Fir, w[x]};
}
bool IsUnion(int a, int b){
    return GetRoot(a).Fir == GetRoot(b).Fir;
}
void Union(int a, int b, int v){
    if(IsUnion(a, b))
        return;

    int aRt = GetRoot(a).Fir;
    w[aRt] = v - w[a];
    root[aRt] = b;
}

int main(){
    fastio;

    while(true){
        int n, m;
        cin >> n >> m;
        if(!n)
            break;

        fill(w, w + 100000, 0);
        for(int i = 1; i <= n; i++)
            root[i] = i;

        char c;
        int a, b;
        while(m--){
            cin >> c >> a >> b;
            if(c == '!'){
                int v;
                cin >> v;
                Union(a, b, v);
            }
            else if(c == '?'){
                if(!IsUnion(a, b)){
                    cout << "UNKNOWN\n";
                    continue;
                }
                GetRoot(a);
                GetRoot(b);
                cout << w[a] - w[b] << '\n';
            }
        }
    }

    return 0;
}
