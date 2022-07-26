namespace DSU{
	
	vector<int> no;
	vector<int> S;

	int find(int x){
		
		if(no[x] == x) return x;
		return no[x] = find(no[x]);
	
	}

	bool merge(int x, int y){
		
		x = find(x);
		y = find(y);

		if(x == y) return false;

		if(S[x] < S[y]) swap(x, y);
		
		no[y] = x;
		S[x] += S[y];

		return true;
	}

	void dsu(int n){
		no = S = vector<int>(n, 1);
		for(int i = 0; i < n; i++) no[i] = i;
	}
}
using namespace DSU;