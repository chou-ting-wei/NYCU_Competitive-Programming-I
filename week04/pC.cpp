// Kattis: Generalized Recursive Functions
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

vector<int> v;
vector<pii> p;
string dp[105][105];
int c, d, flgc = 0, flgd = 0;

string add(string a, string b){
    string s = "";
    int la = a.length(), lb = b.length(), len = max(la, lb) + 5, cnt = 0;
    int ar[len], br[len], ret[len];
    For(i, 0, len-1){
        ar[i] = 0;
        br[i] = 0;
        ret[i] = 0;
    }
    Forr(i, la-1, 0){
        ar[cnt] = (a[i] - '0');
        cnt ++;
    }
    cnt = 0;
    Forr(i, lb-1, 0){
        br[cnt] = (b[i] - '0');
        cnt ++;
    }
    For(i, 0, len-2){
        ret[i] = (ar[i] + br[i]);
    }
    For(i, 0, len-2){
        ret[i+1] += ret[i]/10;
        ret[i] %= 10;
    }
    int flg = 0;
    Forr(i, len-1, 0){
        if(!flg && ret[i] != 0){
            flg = 1;
        }
        if(flg){
            s = s + string(1, '0' + ret[i]);
        }
    }
    return s;
}

string slv(int x, int y){
    if(x > 0 && y > 0){
        if(dp[x][y] == ""){
            for(auto &[a, b] : p){
                dp[x][y] = add(dp[x][y], slv(x-a, y-b));
            }
            if(!flgc) dp[x][y] = add(dp[x][y], string(1, ('0' + c)));
            else dp[x][y] = add(dp[x][y], (string(1, (('0' + (c/10))))) + (string(1,('0' + (c%10)))));
        }
        return dp[x][y];
    }
    else{
        if(!flgd) return string(1, ('0' + d));
        else return (string(1, (('0' + (d/10)))) +  string(1,('0' + (d%10))));
    }
}

int32_t main(){
    getAC();
    int n;
    cin >> n;
    cin.get();
    stringstream ss;

    while(n--){
        flgc = 0;
        flgd = 0;
        For(i, 0, 100){
            For(j, 0, 100){
                dp[i][j] = "";
            }
        }
        v.clear();
        p.clear();
        string s;
        getline(cin, s);
        int sn;
        ss.str("");
        ss.clear();
        ss << s;
        while(ss >> sn){
            v.eb(sn);
        }
        int l = sz(v);
        c = v[l-2];
        d = v[l-1];
        if(c/10) flgc = 1;
        if(d/10) flgd = 1;
        string sp = flgd ? (string(1, (('0' + (d/10)))) + string(1, ('0' + (d%10)))) : string(1, '0' + d);
        dp[0][0] = dp[0][1] = dp[1][0] = sp;

        for(int i = 0; i < l-2; i += 2){
            p.eb(v[i], v[i+1]);
        }
        getline(cin, s);
        ss.str("");
        ss.clear();
        ss << s;
        int flg = 0, nx = 0, ny = 0;
        while(ss >> sn){
            flg ++;
            if(flg == 1){
                nx = sn;
            }
            else{
                flg = 0;
                ny = sn;
                cout << slv(nx, ny) << endl;
            }
        }
        cout << endl;
    }

    time();
    return 0;
}
