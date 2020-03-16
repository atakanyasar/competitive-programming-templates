struct Tree{
	vector<vector<int> >& adj;
	vector<vector<int> > anc;
	vector<vector<int> > cost;
	vector<int> depth;
	vector<int> sub;
	vector<bool> vis;
	int n;
	int root;

	Tree(vector<vector<int> >& a, int N = 1e6, int r = 1): adj(a){
		n = N + 5;
		root = r;
		anc = vector<vector<int> > (25, vector<int>(n, 0));
		depth = vector<int>(n, 0);
		vis = vector<bool> (n, false);
		sub = vector<int> (n, 1);
		
		init(root, -1);
		
		for(int d = 1; d < 25; d++){

			for(int x = 0; x < n; x++){

				anc[d][x] = anc[d - 1][anc[d - 1][x]];

		}

      	}

	} 

	void init(int x, int pre){

		for(int i = 0; i < adj[x].size(); i++){

			int y = adj[x][i];

			if(y == pre)continue;

			anc[0][y] = x;

			depth[y] = depth[x] + 1;

			init(y, x);

			sub[x] += sub[y];

		}
	 
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
