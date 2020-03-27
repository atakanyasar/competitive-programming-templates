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


vector<int> adj[1000005];
struct Tree{
	vector<vector<int> > anc;
	vector<int> depth;
	vector<int> sub;
	vector<bool> vis;
	vector<int> T, X;
	int n;
	int root;

	Tree(int N = 1e6, int r = 1){
		n = N + 5;
		root = r;
		anc = vector<vector<int> > (25, vector<int>(n, 0));
		depth = vector<int>(n, 0);
		vis = vector<bool> (n, false);
		sub = vector<int> (n, 1);
		T = vector<int> (n);
		X = vector<int> (n);
		
		init(root, -1);
		
		for(int d = 1; d < 25; d++){

			for(int x = 0; x < n; x++){

				anc[d][x] = anc[d - 1][anc[d - 1][x]];

			}

		}

	} 

	void init(int x, int pre){

		static int t = 0;

		T[x] = t++;

		for(int i = 0; i < adj[x].size(); i++){

			int y = adj[x][i];

			if(y == pre)continue;

			anc[0][y] = x;

			depth[y] = depth[x] + 1;

			init(y, x);

			sub[x] += sub[y];

		}

		X[x] = t++;
	 
	}

	int LCA(int x, int y){

		if(depth[x] < depth[y])swap(x, y);

		for(int w = (1 << 24), d = 24; d >= 0; w /= 2, d--){
			
			if(depth[x] - depth[y] >= w){
				
				x = anc[d][x];

			}

		}

		if(x == y) return x;

		for(int i = 24; i >= 0; i--){

			if(anc[i][x] != anc[i][y]){

				x = anc[i][x];

				y = anc[i][y];

			}

		}

		return anc[0][x];

	}

	int up(int x, int k){

		for(int w = (1 << 24), d = 24; d >= 0; w /= 2, d--){
			
			if(k >= w){
				
				x = anc[d][x];

				k -= w;
			
			}
		
		}

		return x;

	}

	int dist(int x, int y){

		int l = LCA(x, y);

		return depth[x] + depth[y] - 2 * depth[l];

	}

	bool isparent(int x, int y){

		return LCA(x, y) == x;

	}
	
};


struct TreeCompressor : Tree{
	
	vector<int> aux[1000003];

	TreeCompressor(int n = 1e6):Tree(n){}
	
	void compress(vector<int>& arr){

		sort(all(arr), [&](int x, int y){return T[x] < T[y];});

		int l = sz(arr);

		for(int i = 1; i < l; i++) arr.pb(LCA(arr[i - 1], arr[i]));

		sort(all(arr), [&](int x, int y){return T[x] < T[y];});

		stack<int> st;
		st.push(root);

		for(auto x : arr){
			if(x == st.top()) continue;

			while(T[x] < T[st.top()] || X[x] > X[st.top()]) st.pop();

			aux[st.top()].pb(x);
			aux[x].pb(st.top());
			st.push(x);
		}
	}
};

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	freopen("q.gir", "r", stdin);
	freopen("q.cik", "w", stdout);
	
}
