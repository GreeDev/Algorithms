#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

int main(){
    fastio;
    int n;
    cin >> n;

    lli a = 0, b = 1;
    while(n--){
        lli c = a + b;
        a = b;
        b = c;
    }

    cout << (a + b) * 2;

    return 0;
}
