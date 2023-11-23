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

#define X first
#define Y second

#define ALL(V) V.begin(), V.end()

#define rep(I, S, E) for(int I = (S); I < (E); I++)
#define repq(I, S, E) for(int I = (S); I <= (E); I++)

#define pb push_back
#define epb emplace_back

pll operator+(pll a, pll b){
	return {a.X + b.X, a.Y + b.Y};
}
pll operator-(pll a, pll b){
	return {a.X - b.X, a.Y - b.Y};
}
lli operator*(pll a, pll b){
	return a.X * b.Y - a.Y * b.X;
}
lli CCW(pll a, pll b, pll c){
	return a * b + b * c + c * a;
}

// def end

const int INF = 1e9;
struct SplayTree{
	struct Node{
		Node *l, *r, *p;
		int sz;

		Node(){
			l = r = p = nullptr;
			sz = 1;
		}

		void Update(){
			sz = 1;

			if(l){
				sz += l->sz;
			}
			if(r){
				sz += r->sz;
			}
		}
		void LazyProp(){
			// Do lazy
		}
		int LeftSz(){
			if(!l)
				return 0;
			return l->sz;
		}
		int RightSz(){
			if(!r)
				return 0;
			return r->sz;
		}
	} *root;

	void Init(){
		root = new Node();
		root->r = new Node();
		root->r->p = root;
		root->Update();
	}

	void Rotate(Node* x){
		Node* p = x->p;
		x->p = p->p;
		p->p = x;
		Node *b = nullptr;
		if(p->l == x){
			p->l = x->r;
			b = x->r;
			x->r = p;
		}
		else{
			p->r = x->l;
			b = x->l;
			x->l = p;
		}
		if(b)
			b->p = p;
		
		if(x->p){
			if(x->p->l == p)
				x->p->l = x;
			else
				x->p->r = x;
		}
		else
			root = x;

		p->Update();
		x->Update();
	}

	void Splay(Node* x){
		while(x->p){
			Node* p = x->p;
			if(p->p)
				Rotate((p->p->l == p) == (p->l == x) ? p : x);
			Rotate(x);  
		}
	}

	void GetKth(int k){
		Node* x = root;
		while(true){
            x->LazyProp();
			while(k < x->LeftSz()){
				x = x->l;
                x->LazyProp();
			}
			
			k -= x->LeftSz();
			if(!k--)
				break;
			
			x = x->r;
		}
        x->LazyProp();
		Splay(x);
	}
	void GetInterval(int l, int r){
		GetKth(l - 1);
		Node* temp = root;
		root = temp->r;
		root->p = nullptr;

		GetKth(r - l + 1);
		root->p = temp;
		temp->r = root;
		root = temp;
	}
} sp;

int main(){
	fastio;

	return 0;
}
