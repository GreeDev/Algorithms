#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

int main(){
    fastio;
    int sum = 0;
    for(int i = 0; i < 5; i++){
        int k;
        cin >> k;
        sum += k * k;
    }
    cout << sum % 10;
    return 0;
}
