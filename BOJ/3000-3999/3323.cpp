//3323 삼각형

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;
using pll = pair<lli, lli>;
#define Fir first
#define Sec second

pll p[100000];

pll operator-(pll a, pll b){
    return {a.Fir - b.Fir, a.Sec - b.Sec};
}

ostream& operator<<(ostream& out, pll p){
    out << "(" << p.Fir << ", " << p.Sec << ")";
    return out;
}

bool Comp(pll a, pll b){
    if(a.Sec * b.Fir != b.Sec * a.Fir) return a.Sec * b.Fir < b.Sec * a.Fir;
    return a < b;
}


struct Node{
    int lef, rig;
    vector<pll> cvx;
} seg[400000];

lli CCW(pll a, pll b, pll c){
    return (a.Fir * b.Sec + b.Fir * c.Sec + c.Fir * a.Sec) - (a.Fir * c.Sec + b.Fir * a.Sec + c.Fir * b.Sec);
}

void Init(int n, int lef, int rig){
    seg[n] = {lef, rig};

    vector<pll>& cvx = seg[n].cvx;

    if(lef == rig){
        cvx.push_back(p[lef]);
        return;
    }
    for(int i = lef; i <= rig; i++){
        while(cvx.size() > 1 && CCW(cvx[cvx.size() - 2], cvx.back(), p[i]) >= 0)
            cvx.pop_back();

        cvx.push_back(p[i]);
    }
    Init(n * 2, lef, (lef + rig) / 2);
    Init(n * 2 + 1, (lef + rig) / 2 + 1, rig);
}

lli GetDist(pll line, pll pos){
    return abs(line.Fir * pos.Fir + line.Sec * pos.Sec);
}

bool Query(int n, pll lef, pll rig){

    vector<pll>& cvx = seg[n].cvx;

    if(Comp(seg[n].cvx.back(), lef) || Comp(rig, seg[n].cvx.front()))
        return false;
    if(!Comp(seg[n].cvx.front(), lef) && !Comp(rig, seg[n].cvx.back())){
        int lo = 0, hi = cvx.size() - 1;

        pll l = rig - lef;
        l.Fir = -l.Fir;
        swap(l.Fir, l.Sec);

        while(lo + 3 < hi){
            int m1 = (lo * 2 + hi) / 3, m2 = (lo + hi * 2) / 3;

            lli d1 = GetDist(l, cvx[m1]);
            lli d2 = GetDist(l, cvx[m2]);

            if(d1 < d2)
                hi = m2;
            else
                lo = m1;
        }
        while(lo <= hi){
            if(CCW(lef, rig, cvx[lo]) >= 0)
                return true;
            lo++;
        }
        return false;
    }
    return Query(n * 2, lef, rig) | Query(n * 2 + 1, lef, rig);
}

int main(){
    fastio;
    int n, m;
    cin >> n >> m;
    //srand(time(NULL));
    for(int i = 0; i < n; i++){
        cin >> p[i].Fir >> p[i].Sec;
        //p[i] = {rand() % 10000 + 1, rand() % 10000 + 1};
    }
    sort(p, p + n);
    n = (unique(p, p + n) - p);

    sort(p, p + n, Comp);

    Init(1, 0, n - 1);

    for(int i = 0; i < m; i++){
        pll a, b;
        cin >> a.Fir >> a.Sec >> b.Fir >> b.Sec;
        if(!Comp(a, b))
            swap(a, b);
        if(Query(1, a, b))
            cout << "Y\n";
        else
            cout << "N\n";
    }
}
