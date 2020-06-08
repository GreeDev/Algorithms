#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using vi = vector<int>;

vi v;

int con[51];
int disable;

bool vst[51];

bool IsPrime(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0)
            return false;
    }
    return true;
}

bool Match(int x){
    if(vst[x])
        return false;
    vst[x] = true;
    for(int i = 1; i < v.size(); i++){
        if(i == disable)
            continue;
        if(!vst[i] && IsPrime(v[x] + v[i])){
            if(!con[i] || (con[i] && Match(con[i]))){
                con[i] = x;
                if(con[x]) con[con[x]] = 0;
                con[x] = i;
                return true;
            }
        }
    }
    return false;
}

int main(){
    fastio;

    int n;
    cin >> n;
    int i;
    for(i = 0; i < n; i++){
        int k;
        cin >> k;
        v.push_back(k);
    }
    bool b = false;
    vector<int> res;

    for(int t = 1; t < v.size(); t++){
        if(!IsPrime(v[0] + v[t]))
            continue;

        disable = t;
        fill(con, con + n, 0);
        for(i = 1; i < v.size(); i++){
            if(i == t)
                continue;
            fill(vst, vst + n, false);
            if(!con[i] && !Match(i))
                break;
        }
        if(i == v.size()){
            b = true;
            res.push_back(v[t]);
        }
    }
    sort(res.begin(), res.end());
    if(res.empty()) cout << -1;
    else for(i = 0; i < res.size(); i++) cout << res[i] << " ";

    return 0;
}
