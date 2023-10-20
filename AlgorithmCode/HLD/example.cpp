/*
 * BOJ 22487
 * https://www.acmicpc.net/problem/22487
 * !! 아니 내 코드 길이가 !!
 */

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)
#define endl '\n'

#define rep(I, S, E) for(int I = (S); I < (E); I++)
#define repq(I, S, E) for(int I = (S); I <= (E); I++)

using lli = long long int;

const int MAX_N = 202020;

int v[MAX_N];

struct SegTree{
    static const int NL = -1e9;
    struct Node{
        int l, r;
        lli lmx, rmx;
        lli sum, mx;
        lli lz;
    } seg[MAX_N * 3];

    static Node Merge(const Node& l, const Node& r){
        if(l.mx == NL)
            return r;
        if(r.mx == NL)
            return l;
        return {
                l.l, r.r,
                max(l.lmx, l.sum + r.lmx), max(r.rmx, r.sum + l.rmx),
                l.sum + r.sum, max({l.mx, r.mx, l.rmx + r.lmx}),
                NL
        };
    }
    void Merge(int n){
        seg[n] = Merge(seg[n * 2], seg[n * 2 + 1]);
    }
    void Init(int n, int l, int r){
        seg[n] = {l, r, };
        seg[n].lz = NL;
        if(l == r)
            return;

        Init(n * 2, l, (l + r) / 2);
        Init(n * 2 + 1, (l + r) / 2 + 1, r);
        Merge(n);
    }
    inline void UpdateNode(int n, lli c){
        seg[n].sum = c * (seg[n].r - seg[n].l + 1);
        seg[n].lmx = max(c, seg[n].sum);
        seg[n].rmx = max(c, seg[n].sum);
        seg[n].mx = max(c, seg[n].sum);
        seg[n].lz = c;
    }
    void LazyProp(int n){
        if(seg[n].lz == NL)
            return;

        if(seg[n].l != seg[n].r)
            for(int i : {n * 2, n * 2 + 1})
                UpdateNode(i, seg[n].lz);
        seg[n].lz = NL;
    }
    void Update(int n, int l, int r, lli c) {
        if (seg[n].r < l || r < seg[n].l)
            return;
        if (l <= seg[n].l && seg[n].r <= r) {
            UpdateNode(n, c);
            return;
        }

        LazyProp(n);
        Update(n * 2, l, r, c);
        Update(n * 2 + 1, l, r, c);
        Merge(n);
    }
    constexpr static Node empty_node = {NL, NL, NL, NL, NL, NL, NL};

    Node Query(int n, int l, int r){
        if (seg[n].r < l || r < seg[n].l)
            return empty_node;
        if (l <= seg[n].l && seg[n].r <= r) {
            Node node = seg[n];
            return seg[n];
        }

        LazyProp(n);
        Node res_l = Query(n * 2, l, r);
        Node res_r = Query(n * 2 + 1, l, r);
        return Merge(res_l, res_r);
    }
} seg;

vector<int> e[MAX_N];
int par[MAX_N];
struct HLD{
    int w[MAX_N];
    int dep[MAX_N];
    int dfs[MAX_N], dfsV = 0;

    int DFS(int x = 1, int p = 0){
        w[x] = 1;
        par[x] = p;
        dep[x] = dep[p] + 1;
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
    void DoHLD(int x = 1, int hd = 1){
        head[x] = hd;
        dfs[x] = ++dfsV;
        seg.Update(1, dfs[x], dfs[x], v[x]);
        if(e[x].empty())
            return;

        DoHLD(e[x][0], hd);
        for(int i = 1; i < e[x].size(); i++){
            DoHLD(e[x][i], e[x][i]);
        }
    }

    void Update(int x, int y, int c){
        while(head[x] != head[y]){
            if(dep[head[x]] < dep[head[y]])
                swap(x, y);

            seg.Update(1, dfs[head[x]], dfs[x], c);

            x = par[head[x]];
        }
        if(dep[x] < dep[y])
            swap(x, y);

        seg.Update(1, dfs[y], dfs[x], c);
    }
    lli Query(int x, int y){
        SegTree::Node l, r;
        l = r = SegTree::empty_node;
        while(head[x] != head[y]){
            if(dep[head[x]] > dep[head[y]]){
                l = SegTree::Merge(seg.Query(1, dfs[head[x]], dfs[x]), l);
                x = par[head[x]];
            }
            else{
                r = SegTree::Merge(seg.Query(1, dfs[head[y]], dfs[y]), r);
                y = par[head[y]];
            }
        }
        if(dfs[x] > dfs[y]){
            swap(x, y);
            swap(l, r);
        }
        swap(l.lmx, l.rmx);

        SegTree::Node mid = seg.Query(1, dfs[x], dfs[y]);
        return (SegTree::Merge(l, SegTree::Merge(mid, r))).mx;
    }
} hld;

int main(){
    fastio;

    int n, m;
    cin >> n >> m;
    repq(i, 1, n)
        cin >> v[i];

    rep(i, 1, n){
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    seg.Init(1, 1, n);
    hld.DFS();
    hld.DoHLD();
    while(m--){
        int q, a, b, c;
        cin >> q >> a >> b >> c;
        if(q == 1)
            hld.Update(a, b, c);
        if(q == 2){
            cout << hld.Query(a, b) << endl;
        }
    }
}
