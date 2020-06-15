#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

int main(){
    fastio;
    int n;
    cin >> n;
    cout << (n % 400 == 0 || (n % 100 != 0 && n % 4 == 0));

    return 0;
}
