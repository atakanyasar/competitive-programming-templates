namespace SCC{ 
	/// adj, radj
	vector<vector<int> > comp;
	vector<int> no;
	vector<int> topo;
	vector<bool> vis;

	void Top(int x){
		vis[x] = true;
		for(auto y : adj[x]) if(!vis[y]) Top(y);
		topo.pb(x);
	}
	void rdfs(int x){
		vis[x] = true;
		for(auto y : radj[x]) if(!vis[y]) rdfs(y);
		comp.back().pb(x);
		no[x] = sz(comp) - 1;
	}

	void getSCC(int n){
		
		vis = vector<bool>(n + 1, false);
		no = vector<int>(n + 1);

		for(int i = 1; i <= n; i++){
			if(!vis[i]) Top(i);
		}
		for(int i = 1; i <= n; i++){
			vis[i] = false;
		}

		reverse(all(topo));

		for(auto p : topo){
			if(!vis[p]){
				comp.pb(vector<int>());
				rdfs(p);
			}
		}
	}

}
using namespace SCC;