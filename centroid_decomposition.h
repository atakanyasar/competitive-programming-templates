#include<bits/stdc++.h>
using namespace std;

struct Centroid{     
    vector<vector<int>> tree;
	vector<int> sub;
	vector<bool> mark;

	Centroid(vector<vector<int>>& g){
		tree = g;
	}

	int find_centroid(int x, int pre, int sum){
		for(auto y : tree[x]){
			if(y == pre || mark[y]) continue;
			if(sub[y] > sum / 2) return find_centroid(y, x, sum);
		}
		return x;
	}

	void getsub(int x, int pre){
		sub[x] = 1;
		for(auto y : tree[x]){
			if(y == pre || mark[y]) continue;
			getsub(y, x);
			sub[x] += sub[y];
		}
	}

	void dq(int x){
		getsub(x, -1);
		x = find_centroid(x, -1, sub[x]);
		
		for(auto y : tree[x]){
			if(mark[y]) continue;
		}
		
		
		mark[x] = true;
		for(auto y : tree[x]){
			if(mark[y]) continue;
			dq(y);
		}
	}

	void start(int n){

		sub = vector<int> (n, 1);
		mark = vector<bool> (n, false);
		
		dq(1);
		
		sub.clear();
		mark.clear();
	}
};
