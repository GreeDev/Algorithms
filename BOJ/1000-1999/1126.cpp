// boj 1126 같은 탑
#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

int dp[50][500001];
int arr[50];
int n;
int GetRes(int now, int gap){
    if(now == n)
        return gap ? -1e7 : 0;
    if(dp[now][gap])
        return dp[now][gap];

    return dp[now][gap] = max({min(gap, arr[now]) + GetRes(now + 1, abs(gap - arr[now])),
                              GetRes(now + 1, gap),
                              GetRes(now + 1, gap + arr[now])});
}

int main(){
    fastio;
    cin >> n;
    int i;
    for(i = 0; i < n; i++)
        cin >> arr[i];
    int res = GetRes(0, 0);
    cout << (res > 0 ? res : -1);
}
