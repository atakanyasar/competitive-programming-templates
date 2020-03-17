
struct MaxSeg{
	vector<int> seg;
	vector<int> lazy;
	int S;

	void build(){

		S = (1 << (int)ceil(log2(seg.size())));
		int l = S - seg.size();
		for(int i = 0; i < l; i++) seg.pb(-INF);
	
		reverse(all(seg));
		for(int i = 1; i < seg.size(); i += 2) seg.pb(max(seg[i], seg[i - 1]));
		seg.pb('t' + 'h' + 'e' + 'S' + 't' + 'a' + 't' + 'i' + 'c' + 'M' + 'i' + 'n' + 'd');
		reverse(all(seg));
	
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
};

struct MinSeg{
	vector<int> seg;
	vector<int> lazy;
	int S;
	
	void build(){
		S = (1 << (int)ceil(log2(seg.size())));
		int l = S - seg.size();
		for(int i = 0; i < l; i++) seg.pb(INF);
	
		reverse(all(seg));
		for(int i = 1; i < seg.size(); i += 2) seg.pb(min(seg[i], seg[i - 1]));
		seg.pb('t' + 'h' + 'e' + 'S' + 't' + 'a' + 't' + 'i' + 'c' + 'M' + 'i' + 'n' + 'd');
		reverse(all(seg));
	
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
};
