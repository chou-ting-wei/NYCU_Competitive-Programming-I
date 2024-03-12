// Kattis: Parsing Hex
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

int mul[10];

int32_t main(){
    getAC();
    
    mul[1] = 1;
    For(i, 2, 8){
        mul[i] = mul[i-1]*16;
    }

    string s;
    while(getline(cin, s)){
        vector<char> v;
        int flg = -1, out = 0, len = sz(s);
        For(i, 0, len-1){
            if(flg <= 0 && s[i] == '0'){
                v.eb(s[i]);
                flg = 0;
            }
            else if(flg == 0 && tolower(s[i]) == 'x'){
                v.eb(s[i]);
                flg ++;
            }
            else if(flg > 0){
                if((s[i] >= '0' && s[i] <= '9') || (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'f')){
                    v.eb(s[i]);
                }
                else out = 1;
            }
            else{
                flg = -1;
                v.clear();
            }

            if(out || sz(v) == 10 || (i == (len-1))){
                // cerr << i << " " << len-1 << " " << sz(v) << endl;
                if(sz(v) <= 2){
                    flg = -1;
                    out = 0;
                    v.clear();
                    continue;
                }
                int l = sz(v), mulcnt = l - 2, ans = 0;
                For(i, 0, l - 1){
                    cout << v[i];
                    int tm = v[i] - '0';
                    if(tm > 9) tm = tolower(v[i]) - 'a' + 10;
                    if(i >= 2){
                        // cerr << v[i] << " " << tm << endl;
                        ans += tm * mul[mulcnt];
                        mulcnt --;
                    }
                }
                cout << " " << ans << endl;
                flg = -1;
                out = 0;
                v.clear();
            }
        }
    }

    time();
    return 0;
}
