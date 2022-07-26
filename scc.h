#include<bits/stdc++.h>
using namespace std;

struct SCC{ 
	
	vector<vector<int> > adj, radj;
	vector<vector<int> > comp;
	vector<int> no;
	vector<int> topo;
	vector<bool> vis;

	SCC(vector<vector<int>>& g){
		adj = g;
		radj = vector<vector<int>>(g.size(), vector<int>());
		for(int i = 0; i < g.size(); i++){
			for(int j = 0; j < g[i].size(); j++){
				radj[g[i][j]].push_back(i);
			}
		}
	}

	void top(int x){
		vis[x] = true;
		for(auto y : adj[x]) if(!vis[y]) top(y);
		topo.push_back(x);
	}
	void rdfs(int x){
		vis[x] = true;
		for(auto y : radj[x]) if(!vis[y]) rdfs(y);
		comp.back().push_back(x);
		no[x] = comp.size() - 1;
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

		reverse(topo.begin(), topo.end());

		for(auto p : topo){
			if(!vis[p]){
				comp.push_back(vector<int>());
				rdfs(p);
			}
		}
	}

}
using namespace SCC;