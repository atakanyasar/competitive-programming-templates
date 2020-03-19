struct Fenwick{
	
	vector<int> bit;
	int size;
	
	void modify(int j, int v){
		j++;
		for(; j < size; j += j & -j)bit[j] += v;
	}
	
	int query(int j){
		j++;
		int v = 0;
		for(; j > 0; j -= j & -j)v += bit[j];
		return v;
	}
	
	int rangequery(int a, int b){
		return query(b) - query(a - 1);
	}
	
	void rangeupdate(int a, int b, int v){
		modify(a, v);
		modify(b + 1, -v);
	}
	
	Fenwick(int s){
		s += 3;
		size = s;
		bit = vector<int>(s, 0);
	}
	
};




template<typename T>
struct Fenwick{

	vector<T> bit;
	int size;

	T operation(T& x, T y){
		return x += y;
	}

	void modify(int j, T v){
		j++;
		for(; j < size; j += j & -j) operation(bit[j], v);
	}

	T query(int j){
		j++;
		int v = 0;
		for(; j > 0; j -= j & -j) operation(v, bit[j]);
		return v;
	}

	Fenwick(int s){
		s += 3;
		size = s;
		bit = vector<T>(s, 0);
	}

};
