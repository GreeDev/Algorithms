#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

lli sum[100001];

struct Node{
    int lef, rig;
    int mn, mx;
} seg[404040];

void Init(int n, int lef, int rig){
    if(lef == rig){
        seg[n] = {lef, rig, lef, lef};
        return;
    }
    Init(n * 2, lef, (lef + rig) / 2);
    Init(n * 2 + 1, (lef + rig) / 2 + 1, rig);
    seg[n] = {lef, rig};
    if(sum[seg[n * 2 + 1].mn] < sum[seg[n * 2].mn])
        seg[n].mn = seg[n * 2 + 1].mn;
    else
        seg[n].mn = seg[n * 2].mn;

    if(sum[seg[n * 2].mx] > sum[seg[n * 2 + 1].mx])
        seg[n].mx = seg[n * 2].mx;
    else
        seg[n].mx = seg[n * 2 + 1].mx;
}

int MinQuery(int n, int lef, int rig){
    if(seg[n].rig < lef || rig < seg[n].lef)
        return -1;
    if(lef <= seg[n].lef && seg[n].rig <= rig)
        return seg[n].mn;

    int l = MinQuery(n * 2, lef, rig);
    int r = MinQuery(n * 2 + 1, lef, rig);
    if(l == -1)
        return r;
    if(r == -1)
        return l;

    if(sum[r] < sum[l])
        return r;
    return l;
}

int MaxQuery(int n, int lef, int rig){
    if(seg[n].rig < lef || rig < seg[n].lef)
        return -1;
    if(lef <= seg[n].lef && seg[n].rig <= rig)
        return seg[n].mx;

    int l = MaxQuery(n * 2, lef, rig);
    int r = MaxQuery(n * 2 + 1, lef, rig);
    if(l == -1)
        return r;
    if(r == -1)
        return l;

    if(sum[l] > sum[r])
        return l;
    return r;
}

lli arr[100001];

struct Node2{
    int lef, rig;
    lli l, r, mx, sum;
} seg2[404040], emp = {0, 0, 0, 0, -1000000000, 0};

Node2 MergeNode(Node2 a, Node2 b){
    Node2 ret;
    ret.l = max(a.l, a.sum + b.l);
    ret.r = max(b.r, a.r + b.sum);
    ret.mx = max(a.r + b.l, max(a.mx, b.mx));
    ret.sum = a.sum + b.sum;
    return ret;
}

void Init2(int n, int lef, int rig){
    seg2[n] = {lef, rig, arr[lef], arr[lef], arr[lef], arr[lef]};
    if(lef == rig)
        return;
    Init2(n * 2, lef, (lef + rig) / 2);
    Init2(n * 2 + 1, (lef + rig) / 2 + 1, rig);
    seg2[n] = MergeNode(seg2[n * 2], seg2[n * 2 + 1]);
    seg2[n].lef = lef;
    seg2[n].rig = rig;
}

Node2 Query(int n, int lef, int rig){
    if(seg2[n].rig < lef || rig < seg2[n].lef)
        return emp;
    if(lef <= seg2[n].lef && seg2[n].rig <= rig)
        return seg2[n];
    Node2 a = Query(n * 2, lef, rig);
    Node2 b = Query(n * 2 + 1, lef, rig);
    if(a.mx == -1e9)
        return b;
    if(b.mx == -1e9)
        return a;
    return MergeNode(a, b);
}

int main(){
    fastio;
    int n;
    cin >> n;
    int i;
    for(i = 0 ; i < n; i++){
        cin >> arr[i + 1];
        sum[i + 1] = sum[i] + arr[i + 1];
    }
    Init(1, 0, n);
    Init2(1, 1, n);
    int q;
    cin >> q;
    while(q--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x2 <= y1){
            lli mx = Query(1, x2, y1).mx;

            if(x1 != x2)
                mx = max(mx, sum[MaxQuery(1, x2, y2)] - sum[MinQuery(1, x1 - 1, x2 - 2)]);
            if(y1 != y2)
                mx = max(mx, sum[MaxQuery(1, y1 + 1, y2)] - sum[MinQuery(1, x1 - 1, y1 - 1)]);

            cout << mx << '\n';
            //cout << Query(1, x2, y1).mx << '\n';;
        }
        else{
            cout << sum[MaxQuery(1, x2, y2)] - sum[MinQuery(1, x1 - 1, y1 - 1)] << '\n';
        }
    }
}
