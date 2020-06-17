#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using vi = vector<int>;

vi edge[10001];
vector<vi> res;

stack<int> st;

int scc[10001];
int dfs[10001];
int ord = 1;
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
        vi r;
        while(!st.empty()){
            int tp = st.top();
            scc[tp] = ret;
            r.push_back(tp);
            if(tp == x)
                break;
            st.pop();
        }
        sort(r.begin(), r.end());
        st.pop();
        res.push_back(r);
    }
    return ret;
}

int main(){
    fastio;
    int n, m;
    cin >> n >> m;
    int i;
    for(i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
    }
    for(i = 1; i <= n; i++){
        GetSCC(i);
    }
    cout << res.size() << '\n';
    sort(res.begin(), res.end());
    for(i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size(); j++){
            cout << res[i][j] << ' ';
        }
        cout << "-1\n";
    }
    return 0;
}
