namespace HASH{

	void getexp(vector<int>& exp, int x, int m){
		for(int i = 1; i < sz(exp); i++) exp[i] = exp[i - 1] * x % m;
	}
	void getexp(vector<unsigned int>& exp, unsigned int x){
		for(int i = 1; i < sz(exp); i++) exp[i] = exp[i - 1] * x;
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

	int getpHash(vector<int>& _hash, vector<int>& exp, int x, int m, int l, int r){
		return (_hash[r] - exp[r - l + 1] * _hash[l - 1] % m + m) % m;
	}
	unsigned int getpHash(vector<unsigned int>& _hash, vector<unsigned int>& exp, unsigned int x, int l, int r){
		return (_hash[r] - exp[r - l + 1] * _hash[l - 1]);
	}

	int getsHash(vector<int>& _hash, vector<int>& exp, int x, int m, int l, int r){
		return (_hash[l] - exp[r - l + 1] * _hash[r + 1] % m + m) % m;
	}
	unsigned int getsHash(vector<unsigned int>& _hash, vector<unsigned int>& exp, unsigned int x, int l, int r){
		return (_hash[l] - exp[r - l + 1] * _hash[r + 1]);
	}
}
