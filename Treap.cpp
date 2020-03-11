#include<bits/stdc++.h>
#define pb push_back
#define ii pair<int,int>
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define INF 100000000000000000
#define modulo 1000000007
#define mod 998244353
#define int long long int
using namespace std;

#define rand() (rand() * rand() + rand() + 1)

struct Node{

      int left, right, value, prior;

      void set(int a, int b, int c, int d){
            
            left = a;
            right = b;
            value = c;
            prior = d;

      }
      
      Node(){
            left = right = value = 0;
            prior = 0;
      }

} node[3000000];


namespace Treap{

	int ind = 1;
	int root = 0;

	int new_node(){
		return ind++;
	}

	void split(int curr, int x, int& l, int& r){

		if(!curr) l = r = 0;

		else if(x < node[curr].value){
			split(node[curr].left, x, l, node[curr].left);
			r = curr;
		}
		else{
			split(node[curr].right, x, node[curr].right, r);
			l = curr;
		}

	}

	void merge(int& curr, int l, int r){

		if(!l || !r){
			curr = max(l, r);
		}
		else{
			if(node[l].prior > node[r].prior){
				merge(node[l].right, node[l].right, r);
				curr = l;
			}
			else{
				merge(node[r].left, l, node[r].left);
				curr = r;
			}
		}

	}

	void insert(int& curr, int x, int p){
		
		if(!curr){
			curr = new_node();
			node[curr].set(0, 0, x, p);
		}
		else{
			if(p >= node[curr].prior){
				int temp = curr;
				curr = new_node();
				node[curr].set(0, 0, x, p);

				split(temp, x, node[curr].left, node[curr].right);
			}
			else{
				if(x < node[curr].value) insert(node[curr].left, x, p);
				else insert(node[curr].right, x, p);
			}
		}

	}

	int& search(int& curr, int x){
		if(!curr) return curr;
		if(x == node[curr].value) return curr;
		else if(x < node[curr].value) return search(node[curr].left, x);
		else return search(node[curr].right, x);
	}

	void erase(int x){
		int& curr = search(root, x);
		merge(curr, node[curr].left, node[curr].right);
	}

	ii debug(int x){
            if(!x) return {0, 0};
            int l = node[x].left;
            int r = node[x].right;
            ii P = {node[x].value, node[x].value};
            if(l) {
       //     	cout << node[x].value << " " << node[l].value <<"\n";
            	P.second = max(P.second, debug(node[x].left).second);
            	assert(node[x].prior >= node[l].prior);
            	assert(node[x].value == P.second);
            }
            if(r) {
        //    	cout << node[x].value << " " << node[r].value << "\n";
                  P.first = min(P.first, debug(node[x].right).first);
                  assert(node[x].prior >= node[r].prior);
            	assert(node[x].value == P.first);
            }
            return P;
      }

}

int32_t main(){
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      freopen("q.gir", "r", stdin);
      freopen("q.cik", "w", stdout);
      srand(time(NULL));
      vector<int> arr;
      for(int i = 1; i <= 5000; i++)arr.pb(i);
      for(int i = 0; i < 5000; i++){
      	int w = rand() % sz(arr);
      	Treap::insert(Treap::root, arr[w], rand());
      	arr.erase(arr.begin() + w);
      }
      for(int i = 1; i <= 5000; i++){
      	Treap::erase(i);
      	Treap::debug(Treap::root);
      }
      
 /*     vector<ii> A;
      for(int i = 1; i < Treap::ind; i++){
      	A.emplace_back(node[i].prior, node[i].value);
      }
      sort(all(A),greater<ii>());
      for(int i = 0; i < A.size(); i++) cout << A[i].second << "\n";*/
}
