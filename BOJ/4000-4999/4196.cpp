#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

const int MAXN = 100001;

vector<int> edge[MAXN];

int dfs[MAXN];
int scc[MAXN];
bool vst[MAXN];

int dfsV = 1, sccV = 1;
stack<int> st;

int GetSCC(int x){
    if(dfs[x])
        return dfs[x];
    st.push(x);

    dfs[x] = dfsV++;
    int ret = dfs[x];

    for(int v : edge[x]){
        if(!dfs[v])
            ret = min(ret, GetSCC(v));
        else if(!scc[v])
            ret = min(ret, dfs[v]);
    }
    if(ret == dfs[x]){
        while(st.top() != x){
            scc[st.top()] = sccV;
            st.pop();
        }
        scc[x] = sccV++;
        st.pop();
    }
    return ret;
}

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){

        for(int i = 0; i <= 100000; i++)
            edge[i].clear();
        fill(dfs, dfs + MAXN, 0);
        fill(scc, scc + MAXN, 0);
        fill(vst, vst + MAXN, false);
        dfsV = sccV = 1;

        int n, m;
        cin >> n >> m;
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            edge[a].push_back(b);
        }

        for(int i = 1; i <= n; i++){
            GetSCC(i);
            for(int v : edge[i]){
                if(scc[v] == scc[i])
                    continue;
                vst[scc[v]] = true;
            }
        }
        int ans = 0;
        for(int i = 1; i < sccV; i++){
            if(!vst[i])
                ans++;
        }
        cout << ans << '\n';
    }
}
