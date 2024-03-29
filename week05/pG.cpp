// Kattis: Muddy Hike
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

int arr[1005][1005];
int vis[1005][1005];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
set<int> s;
vector<int> v;
int flg = 0;
int r, c;

void init(){
    For(i, 0, r){
        For(j, 0, c){
            vis[i][j] = 0;
        }
    }
}

void dfs(int x, int y, int k){
    vis[x][y] = 1;
    if(y == c){
        flg = 1;
        return;
    }
    For(i, 0, 3){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx > 0 && ny > 0 && nx <= r && ny <= c){
            if(!vis[nx][ny] && arr[nx][ny] <= k) dfs(nx, ny, k);
        }
        if(flg) return;
    }
}

void slv(int k){
    For(i, 1, r){
        if(!flg && !vis[i][1] && arr[i][1] <= k){
            dfs(i, 1, k);
        }
    }
}

int32_t main(){
    getAC();

    cin >> r >> c;
    For(i, 1, r){
        For(j, 1, c){
            cin >> arr[i][j];
            s.insert(arr[i][j]);
        }
    }

    for(auto a : s){
        v.eb(a);
    }

    int l = 0, rr = sz(v)-1;

    while(l < rr){
        flg = 0;
        init();
        int mid = l + ((rr - l) >> 1);
        slv(v[mid]);
        if(flg){
            rr = mid;
        }
        else{
            l = mid + 1;
        }
    }

    cout << v[l] << endl;

    time();
    return 0;
}
