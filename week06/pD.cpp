// Kattis: Kayaking Trip
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

int b, n, e, sn, sb, se, tmpb, tmpn, tmpe;
vector<int> v;
vector<pair<int, string> > com;

int chkz(string s, int &tb, int &tn, int &te){
    int ret = 0;
    if(s == "bb" && tb >= 2){
        tb -= 2;
        ret = 1;
    }
    else if(s == "nn" && tn >= 2){
        tn -= 2;
        ret = 1;
    }
    else if(s == "ee" && te >= 2){
        te -= 2;
        ret = 1;
    }
    else if(s == "bn" && tb >= 1 && tn >= 1){
        tb --;
        tn --;
        ret = 1;
    }
    else if(s == "ne" && tn >= 1 && te >= 1){
        tn --;
        te --;
        ret = 1;
    }
    else if(s == "be" && tb >= 1 && te >= 1){
        tb --;
        te --;
        ret = 1;
    }
    return ret;
}

int chk(int ans){
    int flg = 1;
    tmpb = b, tmpn = n, tmpe = e;

    for(auto &a : v){
        int ck = 0;
        for(auto &[x, y] : com){
            if(x * a >= ans && chkz(y, tmpb, tmpn, tmpe)){
                ck = 1;
                break;
            }
        }
        if(!ck){
            flg = 0;
            break;
        }
    }

    return flg;
}

int32_t main(){
    getAC();

    cin >> b >> n >> e >> sb >> sn >> se;
    int len = (b + n + e) / 2;

    For(i, 0, len-1){
        int k;
        cin >> k;
        v.eb(k);
    }
    sort(all(v));
    rev(v);

    com.eb(sb + sb , "bb");
    com.eb(sb + sn , "bn");
    com.eb(sn + sn , "nn");
    com.eb(sn + se , "ne");
    com.eb(se + se , "ee");
    com.eb(sb + se , "be");

    sort(all(com));

    int l = 0, r = 100000 * (1000 + 1000), ans = 0;
    while(l <= r){
        int mid = l + ((r - l) >> 1);
        if(chk(mid)){
            l = mid + 1;
            ans = mid;
        }
        else r = mid - 1;
    }

    cout << ans << endl;

    time();
    return 0;
}
