//2505 두번 뒤집기

#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using pii = pair<int, int>;

#define Fir first
#define Sec second

bool CheckArray(vector<int>& v){
    for(int i = 0; i < v.size(); i++)
        if(v[i] != i)
            return false;
    return true;
}
vector<int> p;
pii TestIt(vector<int>& t){
    int mn = 1e9, mx = 0;
    for(int i = 0; i < t.size(); i++){
        if(i != t[i]){
            mn = min(mn, i);
            mx = max(mx, i);
        }
    }
    reverse(t.begin() + mn, t.begin() + (mx + 1));
    //cout << "Chk " << mn << ", " << mx << endl;
    if(CheckArray(t))
        return {mn, mx};
    reverse(t.begin() + mn, t.begin() + (mx + 1));
    return {0, 0};
}

int main(){
    fastio;
    int n;
    cin >> n;

    vector<int> arr(n + 2);
    arr[n + 1] = n + 1;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    for(int i = 0; i <= n; i++){
        if(abs(arr[i] - arr[i + 1]) > 1){
            p.push_back(i);
            p.push_back(i + 1);
        }
    }
    if(p.size() > 1){
        p.erase(p.begin());
        p.pop_back();
    }
    if(p.empty()){
        cout << "1 1\n1 1";
        return 0;
    }
    if(p.size() == 2){
        cout << p[0] << " " << p[1];
        cout << "\n1 1";
        return 0;
    }
    for(int i = 0; i < p.size(); i++){
        for(int j = i + 1; j < p.size(); j++){
            reverse(arr.begin() + p[i], arr.begin() + (p[j] + 1));
            //cout << "test " << p[i] << " ~ " << p[j] <<'\n';
            pii res = TestIt(arr);
            if(res.Fir){
                cout << p[i] << " " << p[j] << '\n';
                cout << res.Fir << " " << res.Sec;
                return 0;
            }
            reverse(arr.begin() + p[i], arr.begin() + (p[j] + 1));
        }
    }
    return 0;
}
