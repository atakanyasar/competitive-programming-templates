struct HASH{
	vector<int> prefix_hash, suffix_hash;
	vector<int> exp;
	string s;
	int X;
	unsigned int M;

	HASH(string str, int x, unsigned int m = ULONG_LONG_MAX){
		s = " " + str + " ";
		prefix_hash = vector<int>(sz(s), 0);
		suffix_hash = vector<int>(sz(s), 0);
		exp = vector<int>(sz(s), 1);
		X = x;
		M = m;
		for(int i = 1; i < sz(exp); i++) exp[i] = exp[i - 1] * x % M;
		for(int i = 1; i < sz(s) - 1; i++){
			prefix_hash[i] = (prefix_hash[i - 1] * x + s[i] - 'a' + 1) % M;
		}
		for(int i = sz(s) - 1; i >= 1; i--){
			suffix_hash[i] = (suffix_hash[i + 1] * x + s[i] - 'a' + 1) % M;
		}
	}

	int prefixHash(int l, int r){
		return (prefix_hash[r] - exp[r - l + 1] * prefix_hash[l - 1] % M + M) % M;
	}

	int suffixHash(int l, int r){
		return (suffix_hash[l] - exp[r - l + 1] * suffix_hash[r + 1] % M + M) % M;
	}
};
