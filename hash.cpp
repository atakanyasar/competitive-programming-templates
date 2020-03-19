namespace HASH{

	unsigned int exp(unsigned int a, int b){
		if(b == 0)return 1;
		if(b % 2)return a * exp(a, b - 1);
		int t = exp(a, b / 2);
		return t * t;
	}
	int exp(int a, int b, int m){
		if(b == 0)return 1;
		if(b % 2)return a * exp(a, b - 1, m) % m;
		int t = exp(a, b / 2, m);
		return t * t % m;
	}

	void prefHash(vector<int>& _hash, string& s, int x, int m){
		for(int i = 1; i < sz(s); i++){
			_hash[i] = (_hash[i - 1] * x + s[i] - 'a' + 1) % m;
		}
	}
	void prefHash(vector<unsigned int>& _hash, string& s, unsigned int x){
		for(int i = 1; i < sz(s); i++){
			_hash[i] = (_hash[i - 1] * x + s[i] - 'a' + 1);
		}
	}
	void suffHash(vector<int>& _hash, string& s, int x, int m){
		for(int i = sz(s) - 1; i >= 1; i--){
			_hash[i] = (_hash[i + 1] * x + s[i] - 'a' + 1) % m;
		}
	}
	void suffHash(vector<unsigned int>& _hash, string& s, unsigned int x){
		for(int i = sz(s) - 1; i >= 1; i--){
			_hash[i] = (_hash[i + 1] * x + s[i] - 'a' + 1);
		}
	}

	int getpHash(vector<int>& _hash, int x, int m, int l, int r){
		return (_hash[r] - exp(x, r - l + 1, m) * _hash[l - 1] % m + m) % m;
	}
	unsigned int getpHash(vector<unsigned int>& _hash, unsigned int x, int l, int r){
		return (_hash[r] - exp(x, r - l + 1) * _hash[l - 1]);
	}

	int getsHash(vector<int>& _hash, int x, int m, int l, int r){
		return (_hash[l] - exp(x, r - l + 1, m) * _hash[r + 1] % m + m) % m;
	}
	unsigned int getsHash(vector<unsigned int>& _hash, unsigned int x, int l, int r){
		return (_hash[l] - exp(x, r - l + 1) * _hash[r + 1]);
	}
}