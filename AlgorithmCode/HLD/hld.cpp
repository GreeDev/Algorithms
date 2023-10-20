#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

const int MAX_N = 505050;

vector<int> e[MAX_N];
int par[MAX_N];
struct HLD{
    int w[MAX_N];
    int dep[MAX_N];
    int dfs[MAX_N], dfsV = 0;

    int DFS(int x, int p){
        w[x] = 1;
        par[x] = p;
        dep[x] = dep[p] + 1;
        dfs[x] = ++dfsV;
        for(int i = 0; i < e[x].size(); i++){
            if(e[x][i] == p){
                if(i + 1 == e[x].size())
                    break;
                swap(e[x][i], e[x].back());
            }
            w[x] += DFS(e[x][i], x);
            if(w[e[x][i]] > w[e[x][0]])
                swap(e[x][i], e[x][0]);
        }
        if(p)
            e[x].pop_back();
        return w[x];
    }

    int head[MAX_N];
    void DoHLD(int x, int hd){
        head[x] = hd;
        if(e[x].size() == 0)
            return;

        DoHLD(e[x][0], hd);
        for(int i = 1; i < e[x].size(); i++){
            DoHLD(e[x][i], hd);
        }
    }

    void Query(int x, int y){
        while(head[x] != head[y]){
            // Check the route direction
            if(dep[x] < dep[y])
                swap(x, y);

            // DO SOMETHING
            // Update(dfs[head[x]], dfs[x], ...);

            x = par[head[x]];
        }
        if(dep[x] < dep[y])
            swap(x, y);

        // DO SOMETHING
        // Update(dfs[y], dfs[x]);
    }
};

int main(){
    fastio;

    
}
