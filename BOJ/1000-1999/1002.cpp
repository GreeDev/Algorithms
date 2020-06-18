#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        lli x1, y1, r1, x2, y2, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        double dist = sqrt(1. * (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        if(x1 == x2 && y1 == y2 && r1 == r2)
            cout << "-1\n";
        else if(dist > r1 + r2 || (dist + r1 < r2 || dist + r2 < r1))
            cout << "0\n";
        else if(dist == r1 + r2 || r2 - r1 == dist || r1 - r2 == dist)
            cout << "1\n";
        else
            cout << "2\n";
    }
    return 0;
}
