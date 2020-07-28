//BOJ 17429 국제 메시 기구

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using vi = vector<int>;
#define pb(X) push_back(X)
using uint = unsigned int;

vi edge[500001];
int w[500001];
int dep[500001], par[500001];

int SetInfo(int x, int p){
    if(w[x])
        return w[x];
    w[x] = 1;
    dep[x] = dep[p] + 1;
    par[x] = p;

    vi& e = edge[x];
    for(int i = 0; i < e.size(); i++){
        if(e[i] == p){
            e.erase(e.begin() + i);
            i--;
        }
        else{
            w[x] += SetInfo(e[i], x);
        }
    }
    return w[x];
}

int v[500001];
int hd[500001], subv[500001];

int nowV = 0;
void HLD(int x, int h){
    v[x] = ++nowV;
    hd[x] = h;
    vi& e = edge[x];

    if(edge[x].empty()){
        subv[x] = nowV;
        return;
    }

    int mxW = 0;
    for(int vst: e){
        if(w[mxW] < w[vst])
            mxW = vst;
    }
    HLD(mxW, h);
    for(int vst: e){
        if(mxW == vst)
            continue;
        HLD(vst, vst);
    }
    subv[x] = nowV;
}

struct Seg{
    int lef, rig;
    uint v;
    uint lSum, lMul;
} seg[2000000];

void InitSeg(int n, int lef, int rig){
    seg[n] = {lef, rig, 0, 0, 1};
    if(lef == rig)
        return;
    InitSeg(n * 2, lef, (lef + rig) / 2);
    InitSeg(n * 2 + 1, (lef + rig) / 2 + 1, rig);
}

void LazyQuery(int n){
    seg[n].v *= seg[n].lMul;
    seg[n].v += seg[n].lSum * (seg[n].rig - seg[n].lef + 1);
    if(seg[n].lef == seg[n].rig){
        seg[n].lMul = 1;
        seg[n].lSum = 0;
        return;
    }
    for(int idx: {n * 2, n * 2 + 1}){
        seg[idx].lMul *= seg[n].lMul;
        seg[idx].lSum = seg[idx].lSum * seg[n].lMul + seg[n].lSum;
    }
    seg[n].lMul = 1;
    seg[n].lSum = 0;
}

uint SegSum(int n, int lef, int rig){
    if(seg[n].rig < lef || rig < seg[n].lef)
        return 0;
    LazyQuery(n);

    if(lef <= seg[n].lef && seg[n].rig <= rig){
        return seg[n].v;
    }
    return SegSum(n * 2, lef, rig) + SegSum(n * 2 + 1, lef, rig);
}

void SegQuery(int n, int lef, int rig, uint mul, uint add){
    LazyQuery(n);
    if(seg[n].rig < lef || rig < seg[n].lef)
        return;

    if(lef <= seg[n].lef && seg[n].rig <= rig){
        seg[n].lMul *= mul;
        seg[n].lSum = seg[n].lSum * mul + add;
        LazyQuery(n);
        return;
    }
    SegQuery(n * 2, lef, rig, mul, add);
    SegQuery(n * 2 + 1, lef, rig, mul, add);

    seg[n].v = seg[n * 2].v + seg[n * 2 + 1].v;
}

void Query13(int x, uint mul, uint add){
    SegQuery(1, v[x], subv[x], mul, add);
}

void Query24(int a, int b, uint mul, uint add){ // road query
    while(hd[a] != hd[b]){
        if(dep[hd[a]] > dep[hd[b]]){
            SegQuery(1, v[hd[a]], v[a], mul, add);
            a = par[hd[a]];
        }
        else{
            SegQuery(1, v[hd[b]], v[b], mul, add);
            b = par[hd[b]];
        }
    }
    SegQuery(1, min(v[a], v[b]), max(v[a], v[b]), mul, add);
}

uint Query5(int x){ // Subtree Sum
    return SegSum(1, v[x], subv[x]);
}

uint Query6(int a, int b){ // road sum
    uint res = 0;
    while(hd[a] != hd[b]){
        if(dep[hd[a]] > dep[hd[b]]){
            res += SegSum(1, v[hd[a]], v[a]);
            a = par[hd[a]];
        }
        else{
            res += SegSum(1, v[hd[b]], v[b]);
            b = par[hd[b]];
        }
    }
    res += SegSum(1, min(v[a], v[b]), max(v[a], v[b]));
    return res;
}

int main(){
    fastio;
    int n, q;
    cin >> n >> q;
    for(int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        edge[a].pb(b);
        edge[b].pb(a);
    }
    SetInfo(1, 0);
    HLD(1, 1);
    InitSeg(1, 1, n);
    while(q--){
        int qry;
        cin >> qry;
        if(qry == 1){
            int x, v;
            cin >> x >> v;
            Query13(x, 1, v);
        }
        if(qry == 2){
            int a, b, v;
            cin >> a >> b >> v;
            Query24(a, b, 1, v);
        }
        if(qry == 3){
            int x, v;
            cin >> x >> v;
            Query13(x, v, 0);
        }
        if(qry == 4){
            int a, b, v;
            cin >> a >> b >> v;
            Query24(a, b, v, 0);
        }
        if(qry == 5){
            int x;
            cin >> x;
            cout << Query5(x) << '\n';
        }
        if(qry == 6){
            int a, b;
            cin >> a >> b;
            cout << Query6(a, b) << '\n';
        }
    }
}
