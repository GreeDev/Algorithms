#include <bits/stdc++.h>

using namespace std;

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
