#include <bits/stdc++.h>
using namespace std;

struct Hash {

    vector<int64_t> prefix_hash, suffix_hash;
	vector<int64_t> exp;
	string s;
	int64_t X;
    uint64_t M;

	Hash(string str, int64_t x, uint64_t m = ULONG_LONG_MAX){
		s = " " + str + " ";
		prefix_hash = vector<int64_t>(s.size(), 0);
		suffix_hash = vector<int64_t>(s.size(), 0);
		exp = vector<int64_t>(s.size(), 1);
		X = x;
		M = m;
		for(int64_t i = 1; i < exp.size(); i++) exp[i] = exp[i - 1] * x % M;
		for(int64_t i = 1; i < s.size() - 1; i++){
			prefix_hash[i] = (prefix_hash[i - 1] * x + s[i] - 'a' + 1) % M;
		}
		for(int64_t i = s.size() - 1; i >= 1; i--){
			suffix_hash[i] = (suffix_hash[i + 1] * x + s[i] - 'a' + 1) % M;
		}
	}

	int64_t prefixHash(int64_t l, int64_t r){
		return (prefix_hash[r] - exp[r - l + 1] * prefix_hash[l - 1] % M + M) % M;
	}

	int64_t suffixHash(int64_t l, int64_t r){
		return (suffix_hash[l] - exp[r - l + 1] * suffix_hash[r + 1] % M + M) % M;
	}

};

struct DoubleHash {

    Hash h1, h2;
    DoubleHash(string s, int64_t x1, int64_t x2, uint64_t m = ULONG_LONG_MAX)
    : h1(s, x1, m), h2(s, x2, m)
    {}

    pair<int64_t, int64_t> prefixHash(int64_t l, int64_t r){
        return {h1.prefixHash(l, r), h2.prefixHash(l, r)};
    }
    pair<int64_t, int64_t> suffixHash(int64_t l, int64_t r){
        return {h1.suffixHash(l, r), h2.suffixHash(l, r)};
    }

};