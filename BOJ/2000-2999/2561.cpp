#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using vi = vector<int>;
#define pb(X) push_back(X)

vi GetP(vi& v){
    vi p;
    for(int i = 1; i < v.size(); i++){
        if(abs(v[i] - v[i - 1]) > 1){
            p.pb(i - 1);
            p.pb(i);
        }
    }
    if(!p.empty()){
        p.erase(p.begin());
        p.pop_back();
    }
    return p;
}

vi res;
void Flip(vi& v, int lef){
    vi p = GetP(v);
    int i, j;
    if(p.empty()){
        for(i = 0; i < res.size() / 2; i ++){
            cout << res[i * 2] << " " << res[i * 2 + 1] << '\n';
        }

        for(; i < 3; i++)
            cout << "1 1\n";
        exit(0);
    }
    if(lef == 0)
        return;

    for(i = 0; i < p.size(); i++){
        for(j = i + 1; j < p.size(); j++){
            reverse(v.begin() + p[i], v.begin() + (p[j] + 1));
            res.pb(p[i]);
            res.pb(p[j]);
            Flip(v, lef - 1);
            res.pop_back();
            res.pop_back();
            reverse(v.begin() + p[i], v.begin() + (p[j] + 1));
        }
    }
}

int main(){
    fastio;
    int n;
    cin >> n;
    vi v(n + 2);
    v[n + 1] = n + 1;
    for(int i = 1; i <= n; i++){
        cin >> v[i];
    }
    Flip(v, 3);
    return 0;
}
