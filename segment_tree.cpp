struct MaxSeg{
	vector<int> seg;
	vector<int> lazy;
	int S;
	const int INF = 1e18;

	void build(){

		S = (1 << (int)ceil(log2(seg.size())));
		int l = S - seg.size();
		for(int i = 0; i < l; i++) seg.push_back(-INF);
	
		reverse(seg.begin(), seg.end());
		for(int i = 1; i < seg.size(); i += 2) seg.push_back(max(seg[i], seg[i - 1]));
		seg.push_back(0);
		reverse(seg.begin(), seg.end());
	
		lazy = vector<int>(seg.size() * 2, 0);
	}
	
	MaxSeg(vector<int>& arr){
		seg = arr;
		build();
	}
	MaxSeg(int n){
		seg = vector<int>(n, 0);
		build();
	}
	
	void push(int j){
		if(j >= seg.size())return;
	
		seg[j] += lazy[j];
		lazy[j * 2] += lazy[j];
		lazy[j * 2 + 1] += lazy[j];
		lazy[j] = 0;
	}
	
	void rangeupdate(int j, int a, int b, int x, int y, int v){
	
		push(j);
	
		if(y < a || b < x || y < x) return;
		
		if(a <= x && y <= b){
			lazy[j] += v;
			push(j);
			push(j * 2);
			push(j * 2 + 1);
		}
		else{
			rangeupdate(j * 2, a, b, x, (x + y) / 2, v);
			rangeupdate(j * 2 + 1, a, b, (x + y) / 2 + 1, y, v);
		}
		if(j * 2 < seg.size()) seg[j] = max(seg[j * 2], seg[j * 2 + 1]); 
	}
	int query(){
		push(1);
		return seg[1];
	}

	int query(int j, int a, int b, int x, int y){
	
		push(j);
	
		if(y < a || b < x || y < x) return -INF;
		
		if(a <= x && y <= b) return seg[j];

		return max(
				query(j * 2, a, b, x, (x + y) / 2), 
				query(j * 2 + 1, a, b, (x + y) / 2 + 1, y)
			    );
	}
	void operator()(int l, int r, int v){
		rangeupdate(1, l, r, 0, S-1, v);
	}
	int operator()(int l, int r){
		return query(1, l, r, 0, S-1);
	}
};

struct MinSeg{
	vector<int> seg;
	vector<int> lazy;
	int S;
	const int INF = 1e18;
	
	void build(){
		S = (1 << (int)ceil(log2(seg.size())));
		int l = S - seg.size();
		for(int i = 0; i < l; i++) seg.push_back(INF);
	
		reverse(seg.begin(), seg.end());
		for(int i = 1; i < seg.size(); i += 2) seg.push_back(min(seg[i], seg[i - 1]));
		seg.push_back(0);
		reverse(seg.begin(), seg.end());
	
		lazy = vector<int>(seg.size() * 2, 0);
	}

	MinSeg(vector<int>& arr){
		seg = arr;
		build();
	}

	MinSeg(int s){
		seg = vector<int>(s, INF);
		build();
	}
	
	void push(int j){
		if(j >= seg.size())return;
	
		seg[j] += lazy[j];
		lazy[j * 2] += lazy[j];
		lazy[j * 2 + 1] += lazy[j];
		lazy[j] = 0;
	}
	
	void rangeupdate(int j, int a, int b, int x, int y, int v){
	
		push(j);
	
		if(y < a || b < x || y < x) return;
		
		if(a <= x && y <= b){
			lazy[j] += v;
			push(j);
			push(j * 2);
			push(j * 2 + 1);
		}
		else{
			rangeupdate(j * 2, a, b, x, (x + y) / 2, v);
			rangeupdate(j * 2 + 1, a, b, (x + y) / 2 + 1, y, v);
		}
		if(j * 2 < seg.size()) seg[j] = min(seg[j * 2], seg[j * 2 + 1]); 
	}
	
	int query(){
		push(1);
		return seg[1];
	}

	int query(int j, int a, int b, int x, int y){
	
		push(j);
	
		if(y < a || b < x || y < x) return INF;
		
		if(a <= x && y <= b) return seg[j];

		return min(
				query(j * 2, a, b, x, (x + y) / 2), 
				query(j * 2 + 1, a, b, (x + y) / 2 + 1, y)
			    );
	}
	void operator()(int l, int r, int v){
		rangeupdate(1, l, r, 0, S-1, v);
	}
	int operator()(int l, int r){
		return query(1, l, r, 0, S-1);
	}
};




struct SumSeg{
	vector<int> seg;
	vector<int> lazy;
	vector<int> sub;
	int S;

	void initsub(int j, int l, int r){
		sub[j] = (r - l + 1);
		if(l == r) return;
		initsub(j * 2, l, (l + r) / 2);
		initsub(j * 2 + 1, (l + r) / 2 + 1, r);
	}
	void build(){

		S = (1 << (int)ceil(log2(seg.size())));
		int l = S - seg.size();
		for(int i = 0; i < l; i++) seg.push_back(0);
	
		reverse(seg.begin(), seg.end());
		for(int i = 1; i < seg.size(); i += 2) seg.push_back(seg[i] + seg[i - 1]);
		seg.push_back(0);
		reverse(seg.begin(), seg.end());
	
		lazy = vector<int>(seg.size() * 2, 0);
		sub = vector<int>(seg.size(), 0);
		initsub(1, 0, S - 1);
	}

	
	SumSeg(vector<int>& arr){
		seg = arr;
		build();
	}
	SumSeg(int n){
		seg = vector<int>(n, 0);
		build();
	}
	
	void push(int j){
		if(j >= seg.size())return;
	
		seg[j] += lazy[j] * sub[j];
		lazy[j * 2] += lazy[j];
		lazy[j * 2 + 1] += lazy[j];
		lazy[j] = 0;
	}
	
	void rangeupdate(int j, int a, int b, int x, int y, int v){
	
		push(j);
	
		if(y < a || b < x || y < x) return;
		
		if(a <= x && y <= b){
			lazy[j] += v;
			push(j);
			push(j * 2);
			push(j * 2 + 1);
		}
		else{
			rangeupdate(j * 2, a, b, x, (x + y) / 2, v);
			rangeupdate(j * 2 + 1, a, b, (x + y) / 2 + 1, y, v);
		}
		if(j * 2 < seg.size()) seg[j] = seg[j * 2] + seg[j * 2 + 1]; 
	}
	int query(){
		push(1);
		return seg[1];
	}

	int rangequery(int j, int a, int b, int x, int y){
	
		push(j);
	
		if(y < a || b < x || y < x) return 0;
		
		if(a <= x && y <= b) return seg[j];

		return rangequery(j * 2, a, b, x, (x + y) / 2) + rangequery(j * 2 + 1, a, b, (x + y) / 2 + 1, y);
	}
	void operator()(int l, int r, int v){
		rangeupdate(1, l, r, 0, S-1, v);
	}
	int operator()(int l, int r){
		return rangequery(1, l, r, 0, S-1);
	}
};
