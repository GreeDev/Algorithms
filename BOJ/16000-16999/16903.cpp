#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using uint = unsigned int;

struct BitTree{
    int ct = 0;

    BitTree *lef, *rig;
    BitTree() {
        lef = rig = nullptr;
    }

    void Update(){
        ct = 0;
        if(lef) ct += lef->ct;
        if(rig) ct += rig->ct;
    }

    void Insert(uint value, int depth = 29){
        if(depth == -1){
            ct++;
            return;
        }
        if(value & (1 << depth)){
            if(rig == nullptr)
                rig = new BitTree();
            rig->Insert(value, depth - 1);
        }
        else{
            if(lef == nullptr)
                lef = new BitTree();
            lef->Insert(value, depth - 1);
        }

        Update();
    }

    void Erase(uint value, int depth = 29){
        if(depth == -1){
            ct--;
            return;
        }
        if(value & (1 << depth))
            rig->Erase(value, depth - 1);
        else
            lef->Erase(value, depth - 1);

        Update();
    }

    uint FindMax(uint val, int depth = 29){
        if(depth == -1)
            return 0;

        if(!lef || lef->ct == 0)
            return rig->FindMax(val, depth - 1) | (1 << depth);
        if(!rig || rig->ct == 0)
            return lef->FindMax(val, depth - 1);

        if(((val >> depth) & 1) ^ 1)
            return rig->FindMax(val, depth - 1) | (1 << depth);
        return lef->FindMax(val, depth - 1);
    }
};

int main(){
    fastio;
    BitTree bt;
    bt.Insert(0);
    int Q;
    cin >> Q;

    while(Q--){
        int q;
        uint v;
        cin >> q >> v;
        if(q == 1)
            bt.Insert(v);
        if(q == 2)
            bt.Erase(v);
        if(q == 3)
            cout << (bt.FindMax(v) ^ v) << '\n';
    }
    return 0;
}