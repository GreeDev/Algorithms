#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

int main(){
    fastio;
    int ct = 0;
    bitset<42> b;

    for(int i = 0; i < 10; i++){
        int k;
        cin >> k;
        b.set(k % 42);
    }
    cout << b.count();
    return 0;
}
