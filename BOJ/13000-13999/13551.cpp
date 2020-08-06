//BOJ 13551 원과 쿼리

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

using pll = pair<lli, lli>;
#define Fir first
#define Sec second

pll p[100000];

lli GetDist(pll a, pll b){
    return (a.Fir - b.Fir) * (a.Fir - b.Fir) + (a.Sec - b.Sec) * (a.Sec - b.Sec);
}

struct Area{
    lli lx, rx, ly, ry;
    vector<pll> v;

    int InCircle(pll o, lli r){
        bool a = (GetDist(pll(lx, ly), o) <= r);
        bool b = (GetDist(pll(lx, ry), o) <= r);
        bool c = (GetDist(pll(rx, ly), o) <= r);
        bool d = (GetDist(pll(rx, ry), o) <= r);
        if(a && b && c && d)
            return 2;

        if(a || b || c || d)
            return 1;
        bool xCol = (lx <= o.Fir && o.Fir <= rx);
        bool yCol = (ly <= o.Sec && o.Sec <= ry);
        if(xCol && yCol)
            return 1;
        if(xCol)
            return min(abs(ly - o.Sec), abs(ry - o.Sec)) * min(abs(ly - o.Sec), abs(ry - o.Sec)) <= r;
        if(yCol)
            return min(abs(lx - o.Fir), abs(rx - o.Fir)) * min(abs(lx - o.Fir), abs(rx - o.Fir)) <= r;
        return 0;
    }
};
vector<lli> x, y, cpx, cpy;

int main(){
    fastio;
    int n;
    cin >> n;
    x.resize(n); y.resize(n);
    for(int i = 0; i < n; i++){
        cin >> p[i].Fir >> p[i].Sec;
        x[i] = p[i].Fir; y[i] = p[i].Sec;
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    vector<Area> area;

    int xsz = min((int)x.size() - 1, 70);
    for(int i = 0; i <= xsz; i++)
        cpx.push_back(x[i * (x.size() - 1) / (xsz + !xsz)]);
    if(cpx.size() == 1)
        cpx.push_back(cpx.back());

    int ysz = min((int)y.size() - 1, 70);
    for(int i = 0; i <= ysz; i++)
        cpy.push_back(y[i * (y.size() - 1) / (ysz + !ysz)]);
    if(cpy.size() == 1)
        cpy.push_back(cpy.back());

    for(int i = 1; i < cpx.size(); i++)
        cpx[i]++;
    for(int i = 1; i < cpy.size(); i++)
        cpy[i]++;

    for(int i = 0; i < cpx.size() - 1; i++)
        for(int j = 0; j < cpy.size() - 1; j++){
            area.push_back({cpx[i], cpx[i + 1] - 1, cpy[j], cpy[j + 1] - 1});
        }

    for(int i = 0; i < n; i++){
        int xv = upper_bound(cpx.begin(), cpx.end() - 1, p[i].Fir) - cpx.begin() - 1;
        int yv = upper_bound(cpy.begin(), cpy.end() - 1, p[i].Sec) - cpy.begin() - 1;

        int idx = xv * (cpy.size() - 1) + yv;
        area[idx].v.push_back(p[i]);
    }

    int Q;
    cin >> Q;
    while(Q--){
        pll o;
        lli r;
        cin >> o.Fir >> o.Sec >> r;
        int ct = 0;
        r *= r;
        for(int i = 0; i < area.size(); i++){
            int t = area[i].InCircle(o, r);
            if(t == 2)
                ct += area[i].v.size();
            if(t == 1){
                for(int j = 0; j < area[i].v.size(); j++)
                    ct += (GetDist(area[i].v[j], o) <= r);
            }
        }
        cout << ct << '\n';
    }
}
