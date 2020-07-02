//10165 버스 노선

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using pii = pair<int, int>;
#define Fir first
#define Sec second


struct Bus{
    pii p;
    int idx;

    bool operator<(const Bus& cmp){
        if(p.Sec != cmp.p.Sec)
            return p.Sec < cmp.p.Sec;
        return p.Fir > cmp.p.Fir;
    }
};

vector<Bus> v;

bool Inside(pii l, pii t){
    return l.Fir <= t.Fir && t.Sec <= l.Sec;
}
bool CompIdx(Bus a, Bus b){
    return a.idx < b.idx;
}

int main(){
    fastio;

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        if(a > b)
            b += n;
        v.push_back({{a, b}, i + 1});
    }
    sort(v.begin(), v.end());
    deque<Bus> dq;
    for(int i = 0; i < m; i++){
        while(!dq.empty() && Inside(v[i].p, dq.back().p))
            dq.pop_back();
        dq.push_back(v[i]);
    }

    Bus p = dq.back();
    p.p.Fir -= n;
    p.p.Sec -= n;
    while(dq.size() > 1 && Inside(p.p, dq.front().p))
        dq.pop_front();

    sort(dq.begin(), dq.end(), CompIdx);
    for(int i = 0; i < dq.size(); i++)
        cout << dq[i].idx << " ";
    return 0;
}
