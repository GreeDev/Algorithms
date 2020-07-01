#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

int p[1001];

int main(){
    //fastio;

    int n;
    cin >> n;

    vector<int> r;
    for(int i = 0; i < n; i++){
        int k;
        cin >> k;
        r.push_back(k);
        p[k]++;
    }
    sort(r.begin(), r.end());
    r.erase(unique(r.begin(), r.end()), r.end());

    queue<int> temp;
    vector<int> res;
    res.push_back(-2);
    temp.push(r[0]);
    for(int i = 1; i < r.size(); i++){
        if(i + 1 == r.size()){
            if(!temp.empty() && res.back() + 1 != temp.front() && temp.front() + 1 != r[i]){
                while(p[temp.front()]-- > 0)
                    res.push_back(temp.front());
                temp.pop();
            }
            if(temp.front() + 1 != r[i]){
                res.push_back(r[i]);
                p[r[i]]--;
                if(!temp.empty()){
                    while(p[temp.front()]-- > 0)
                        res.push_back(temp.front());
                    temp.pop();
                }
            }
            while(p[r[i]]-- > 0)
                res.push_back(r[i]);
            break;
        }

        if(!temp.empty()){
            if(res.back() + 1 == temp.front()){
                res.push_back(r[i]);
                p[r[i]]--;
            }
            int pt = temp.front();
            while(p[pt]-- > 0)
                res.push_back(pt);
            temp.pop();
        }

        if(p[r[i]] <= 0)
            continue;

        temp.push(r[i]);
    }
    if(!temp.empty()){
        while(p[temp.front()]-- > 0)
            res.push_back(temp.front());
        temp.pop();
    }

    for(int i = 1; i < res.size(); i++)
        cout << res[i] << " ";
    return 0;
}
