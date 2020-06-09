#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

char prt[2187][2188];


void PrintStar(int x, int y, int sz){
    if(sz == 1){
        prt[x][y] = '*';
        return;
    }

    int sz3 = sz / 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i == 1 && i == j)
                continue;
            PrintStar(x + sz3 * i, y + sz3 * j, sz3);
        }
    }
}

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        fill(prt[i], prt[i] + n, ' ');

    PrintStar(0, 0, n);
    for(int i = 0; i < n; i++)
        printf("%s\n", prt[i]);
    return 0;
}
