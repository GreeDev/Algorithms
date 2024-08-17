#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

// def start

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)
#define endl '\n'

using lli = long long int;
using pll = pair<lli, lli>;
using pii = pair<int, int>;

using Ld = long double;

#define X first
#define Y second

#define ALL(V) V.begin(), V.end()

#define rep(I, S, E) for(int I = (S); I < (E); I++)
#define repq(I, S, E) for(int I = (S); I <= (E); I++)

#define pb push_back
#define epb emplace_back

// def end

vector<int> e[101010], e2[101010];

bool Comp(int a, int b) {
    if(e[a].size() == e[b].size())
        return a < b;
    return e[a].size() < e[b].size();
}

bool tenko[101010];
bool shibuki[101010];

bitset<500> yes[101010];

int main(){
    fastio;
    int N, M;
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b;
        cin >> a >> b;
        e[a].pb(b); e[b].pb(a);
    }

    vector<int> vtx;
    repq(i, 1, N) {
        vtx.pb(i);
        for(int v : e[i]) {
            if(Comp(i, v))
                e2[i].pb(v);
        }
        sort(ALL(e2[i]));
    }

    int res = 0;
    sort(ALL(vtx), Comp);

    for(int i : vtx) {
        vector<int> v1s;
        for(int v1 : e2[i]) {
            if (shibuki[v1])
                continue;
            v1s.pb(v1);
            tenko[v1] = true;
        }
        for(int v1 : v1s) { // K
            int k = 0;
            yes[v1].reset();
            for(int v2 : e2[v1]) { // K?
                while(k < v1s.size() && v1s[k] < v2) k++;

                if(k < v1s.size() && v1s[k] == v2)
                    yes[v1].set(k);
            }
        }
        for(int v1 : v1s) {
            for(int v2 : e2[v1]) {
                if(!tenko[v2])
                    continue;
                res += (yes[v1] & yes[v2]).count();
            }
        }
        for(int v1 : v1s)
            tenko[v1] = false;

        shibuki[i] = true;
    }
    cout << res;

    return 0;
}

// K = sqrtN
// K^2 + (K - 1)^2 + ... = K^3 / 6 ? 아마 2배 해서 K^3 / 3 정도일듯??
// counting = K^3 / 6 * (K / w) = K^4 / w = N^2 / w
// ???
