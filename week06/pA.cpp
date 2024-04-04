// Kattis: Arachnophobia
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
const int INF = 1e18;
 
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

vector<pii> g[200005];
vector<int> vis(100005), diss(100005, INF), dis(100005, INF), sp;

int st, en, n, m, t;

int chk(int in){
    if(diss[st] < in || diss[en] < in) return 0;
    fill(all(vis), 0);
    fill(all(dis), INF);

    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.emplace(0, st);
    dis[st] = 0;

    For(i, 0, n-1){
        if(diss[i] < in) vis[i] = 1;
    }

    while(!pq.empty()){
        auto [dv, v] = pq.top(); pq.pop();
        if(vis[v]) continue;
        vis[v] = 1;

        for(auto &[u, w] : g[v]){
            if(dis[u] > dis[v] + w){
                dis[u] = dis[v] + w;
                pq.emplace(dis[u], u);
            }
        }
    }

    return (dis[en] <= t);
}

int32_t main(){
    getAC();

    cin >> n >> m >> t;

    For(i, 0, m-1){
        int x, y, w;
        cin >> x >> y >> w;
        g[x].eb(y, w);
        g[y].eb(x, w);
    }

    cin >> st >> en;

    int s;
    cin >> s;

    For(i, 0, s-1){
        int k;
        cin >> k;
        sp.eb(k);
    }

    priority_queue<pii, vector<pii>, greater<pii> > pqs;
    for(auto &a : sp){
        pqs.emplace(0, a);
        diss[a] = 0;
    }

    while(!pqs.empty()){
        auto [dv, v] = pqs.top(); pqs.pop();
        if(vis[v]) continue;
        vis[v] = 1;

        for(auto &[u, w] : g[v]){
            if(diss[u] > diss[v] + w){
                diss[u] = diss[v] + w;
                pqs.emplace(diss[u], u);
            }
        }
    }

    int l = 0, r = INF, ans = INF;
    while(l <= r){
        int mid = l + ((r - l) >> 1);
        if(chk(mid)){
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }

    cout << ans << endl;

    time();
    return 0;
}
