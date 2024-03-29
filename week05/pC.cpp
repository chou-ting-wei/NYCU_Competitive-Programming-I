// Kattis: Faulty Robot
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

int n, m;
int flg[1005];
int used[1005];
vector<pii> v[1005];
vector<int> cy, tcy;

struct DSU{
    int p[1005];
    int flg[1005];
    void init(int k){
        For(i, 0, k){
            p[i] = i;
            flg[i] = 0;
        }
    }
    int findp(int x){
        if(x == p[x]) return x;
        return p[x] = findp(p[x]);
    }
    void uni(int x, int y){
        int px = findp(x), py = findp(y);
        if(px != py){
            p[px] = py;
        }
    }
    void tag(int x){
        flg[findp(x)] = 1;
    }
    int same(int x, int y){
        return findp(x) == findp(y);
    }
}d;

void init(){
    For(i, 0, n){
        used[i] = 0;
    }
}

void dfs(int k){
    used[k] = 1;
    cy.eb(k);
    for(auto &[x, y] : v[k]){
        if(x == 1){
            if(!used[y]) dfs(y);
            else{
                for(auto a : cy){
                    flg[a] = 1;
                }
            }
        }
    }
    cy.pop_back();
}

void slv(int k){
    used[k] = 1;
    int cnt = 0;
    for(auto &[x, y]: v[k]){
        if(x == 1){
            cnt ++;
            if(!used[y]) slv(y);
        }
        else{
            if(!flg[y] && !d.same(k, y)){
                d.tag(y);
            }
        }
    }
    if(cnt == 0 && !flg[k]){
        d.tag(k);
    }
}

int32_t main(){
    getAC();

    cin >> n >> m;
    d.init(n);
    For(i, 1, m){
        int x, y;
        cin >> x >> y;
        if(x < 0){
            d.uni(-x, y);
            v[-x].eb(1, y);
            tcy.eb(-x);
        }
        else{
            v[x].eb(0, y);
        }
    }

    for(auto &a : tcy){
        if(!used[a]){
            dfs(a);
        }
    }

    init();
    slv(1);

    int ans = 0;
    For(i, 1, n){
        ans += d.flg[i];
    }
    cout << ans << endl;

    time();
    return 0;
}
