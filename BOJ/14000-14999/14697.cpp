#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

bool dp[301];
int main(){
    fastio;
    int a, b, c, n;
    cin >> a >> b >> c >> n;
    dp[0] = true;
    for(int i = a; i <= n; i++){
        dp[i] |= dp[i - a];
    }
    for(int i = b; i <= n; i++){
        dp[i] |= dp[i - b];
    }
    for(int i = c; i <= n; i++){
        dp[i] |= dp[i - c];
    }
    cout << dp[n];
    return 0;
}
