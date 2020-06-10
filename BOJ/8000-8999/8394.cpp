
/* 

수열의 주기로 최적화 가능

*/

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
        lli c = (a + b) % 10;
        a = b;
        b = c;
    }

    cout << b;

    return 0;
}
