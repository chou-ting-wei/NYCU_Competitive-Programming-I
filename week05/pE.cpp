// Kattis: Almost Union-Find
//
//  main.cpp
//  C++
//
//  Created by userwei
//

#ifdef LOCAL
    #include "/Users/chou.ting.wei/Coding/stdc++.h"
#else
    #include <bits/stdc++.h>
    #pragma GCC optimize("Ofast")
    #pragma GCC optimize("unroll-loops")
    #pragma GCC target("avx2")
#endif
 
#define int long long
#define ull unsigned long long

#define For(z, x, y) for(int z = x; z <= y; z ++)
#define Forr(z, x, y) for(int z = x; z >= y; z --)
#define lowbit(x) ((x) & -(x))
 
#define ef emplace_front
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define sz(x) ((int) x.size())
#define rev(x) reverse(all(x))
 
#define mp make_pair
#define pii pair<int, int>
#define pdd pair<double, double>
#define F first
#define S second
 
#define endl '\n'
 
using namespace std;
 
template<typename T> inline void chmin(T &_a, const T &_b) { if(_b < _a) _a = _b; }
template<typename T> inline void chmax(T &_a, const T &_b) { if(_b > _a) _a = _b; }
 
clock_t start;
 
void getAC(){
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
        start = clock();
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}
 
void time(){
    #ifdef LOCAL
        cerr << "Execution Time : " << double(clock() - start) / CLOCKS_PER_SEC << " (s)" << endl;
        fclose(stdin), fclose(stdout), fclose(stderr);
    #endif
}
 
int max(int a, int b) { return a > b ? a : b; }
int gcd(int a, int b) { if(a == 0) return b; return b == 0 ? a : gcd(b, a % b); }
 
void YES(bool b) { cout << (b ? "YES" : "NO") << endl; }
void Yes(bool b) { cout << (b ? "Yes" : "No") << endl; }
void sto(int k, int m) { cout << (k ? " " : "") << m; }
 
const double PI = acos(-1);
const int INF = 5000000000000000000;
 
struct custom_hash{
    // unordered_map<int, int, custom_hash> safe_map;
    // gp_hash_table<int, int, custom_hash> safe_hash_table;
    static uint64_t splitmix64(uint64_t x){
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const{
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct DSU{
    int p[200005], s[200005], sum[200005];
    void init(int k){
        for(int i = 1, j = k + 1; i <= k; i ++, j ++){
            p[i] = j;
            p[j] = j;
            s[j] = 1;
            sum[j] = i;
        }
        
    }
    int findp(int c){
        if(p[c] == c) return c;
        return p[c] = findp(p[c]);
    }
    void uni(int x, int y){
        int px = findp(x), py = findp(y);
        if(px != py){
            s[py] += s[px];
            sum[py] += sum[px];
            p[px] = py;
        }
    }
    void move(int x, int y){
        int px = findp(x), py = findp(y);
        if(px != py){
            s[py] ++;
            s[px] --;
            sum[py] += x;
            sum[px] -= x;
            p[x] = py;
        }
    }
    int same(int x, int y){
        return findp(x) == findp(y);
    }
} d;

int32_t main(){
    getAC();

    int n, m;
    while(cin >> n >> m){
        d.init(n);
        For(i, 1, m){
            int c;
            cin >> c;
            if(c == 1){
                int a, b;
                cin >> a >> b;
                d.uni(a, b);
            }
            else if(c == 2){
                int a, b;
                cin >> a >> b;
                d.move(a, b);
            }
            else{
                int k;
                cin >> k;
                int pk = d.findp(k);
                cout << d.s[pk] << " " << d.sum[pk] << endl;
            }
        }
    }

    time();
    return 0;
}
