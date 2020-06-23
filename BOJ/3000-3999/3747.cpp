#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

const int MAXN = 2001;

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
    while(!cin.eof()){
        int n, m;
        cin >> n;
        if(cin.eof())
            break;
        cin >> m;
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            edge[n - a].push_back(n + b);
            edge[n - b].push_back(n + a);
        }
        for(int i = 0; i <= n * 2; i++){
            GetSCC(i);
        }
        bool f = false;
        for(int i = 1; i <= n; i++){
            if(scc[n + i] == scc[n - i]){
                cout << "0\n";
                f = true;
                break;
            }
        }
        if(!f)
            cout << "1\n";
        for(int i = 0; i < MAXN; i++)
            edge[i].clear();
        fill(scc, scc + MAXN, 0);
        fill(dfs, dfs + MAXN, 0);
        fill(vst, vst + MAXN, false);
        dfsV = sccV = 1;
    }

    return 0;
}
