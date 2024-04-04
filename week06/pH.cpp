// Kattis: Just for Sidekicks
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

const int MAXN = 2e5 + 5;

int arr[MAXN], val[10];

struct SEG{
    int seg[4 * MAXN][10];

    void pull(int id){
        For(i, 1, 6){
            seg[id][i] = seg[id * 2][i] + seg[id * 2 + 1][i];
        }
    }
    void build(int l, int r, int id = 1){
        if(l == r){
            For(i, 1, 6){
                seg[id][i] = 0;
            }
            seg[id][arr[l]] = 1;
            return;
        }
        int mid = l + ((r - l) >> 1);
        build(l, mid, id * 2);
        build(mid + 1, r, id * 2 + 1);
        pull(id);
    }
    int cal(int id){
        int ret = 0;
        For(i, 1, 6){
            ret += seg[id][i] * val[i];
        }
        return ret;
    }
    int query(int ql, int qr, int l, int r, int id = 1){
        if(ql > r || qr < l) return 0;
        if(ql <= l && r <= qr) return cal(id);
        int mid = l + ((r - l) >> 1);
        return query(ql, qr, l, mid, id * 2) + query(ql, qr, mid + 1, r, id * 2 + 1);
    }
    void modify(int x, int v, int l, int r, int id = 1){
        if(x < l || x > r) return;
        if(l == r){
            For(i, 1, 6){
                seg[id][i] = 0;
            }
            seg[id][v] = 1;
            return;
        }
        int mid = l + ((r - l) >> 1);
        modify(x, v, l, mid, id * 2);
        modify(x, v, mid + 1 ,r, id * 2 + 1);
        pull(id);
    }
}sg;


int32_t main(){
    getAC();

    int n, q;
    cin >> n >> q;

    For(i, 1, 6) cin >> val[i];

    string s;
    cin >> s;

    For(i, 0, n-1){
        arr[i + 1] = s[i] - '0';
    }

    sg.build(1, n);

    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int k, p;
            cin >> k >> p;
            sg.modify(k, p, 1, n);
        }
        else if(t == 2){
            int p, v;
            cin >> p >> v;
            val[p] = v;
        }
        else{
            int l, r;
            cin >> l >> r;
            cout << sg.query(l, r, 1, n) << endl;
        }
    }

    time();
    return 0;
}
