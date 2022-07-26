#include<bits/stdc++.h>
using namespace std;

namespace Math
{
    vector<int> fact;
    int M;

    int exp(int a, int b, int m = M)
    {
        if (b == 0)
            return 1;
        if (b % 2)
            return a * exp(a, b - 1, m) % m;
        int t = exp(a, b / 2, m);
        return t * t % m;
    }

    int inv(int a)
    {
        return exp(a, M - 2);
    }

    int comb(int n, int r)
    {
        if (r == 0 || r == n)
            return 1;
        return fact[n] * inv(fact[r]) % M * inv(fact[n - r]) % M;
    }
    bool isprime(int x)
    {
        for (int i = 2; i * i <= x; i++)
        {
            if (x % i == 0)
                return false;
        }
        return true;
    }
    vector<int> divisors(int x)
    {
        vector<int> ret;
        for (int i = 1; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                ret.push_back(i);
                if (i * i != x)
                    ret.push_back(x / i);
            }
        }
        return ret;
    }
    vector<int> prime_fac(int x)
    {
        vector<int> ret;
        for (int i = 2; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                ret.push_back(i);
                while (x % i == 0)
                    x /= i;
            }
        }
        if (x > 1)
            ret.push_back(x);
        return ret;
    }
    void Math_init(int m = 1000000007)
    {
        fact = vector<int>(2000006, 1);
        M = m;
        for (int i = 1; i < fact.size(); i++)
            fact[i] = fact[i - 1] * i % M;
    }
};
using namespace Math;
