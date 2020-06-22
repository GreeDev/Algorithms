#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

vector<int> edge[20001];

int scc[20001], sccCount = 1;
int dfs[20001], ord = 1;

stack<int> st;

int GetSCC(int x){
    if(dfs[x])
        return dfs[x];
    st.push(x);
    dfs[x] = ord++;
    int ret = dfs[x];
    for(int v : edge[x]){
        if(!dfs[v])
            ret = min(ret, GetSCC(v));
        else if(!scc[v])
            ret = min(ret, dfs[v]);
    }
    if(ret == dfs[x]){
        while(st.top() != x){
            scc[st.top()] = sccCount;
            st.pop();
        }
        scc[x] = sccCount++;
        st.pop();
    }
    return ret;
}

int main(){
    fastio;

    int n, m;
    cin >> n >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
        edge[n - a].push_back(n + b);
        edge[n - b].push_back(n + a);
    }
    for(int i = 0; i <= n * 2; i++){
        GetSCC(i);
    }
    bool f = false;
    for(int i = 1; !f && i < n; i++){
        f = (scc[n + i] == scc[n - i]);
    }
    cout << !f;
    return 0;
}
