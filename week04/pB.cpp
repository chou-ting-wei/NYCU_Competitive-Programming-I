// Kattis: Wizard of Odds
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

int a[105], b[105], t[105], c[105];

int cmp(int x[], int y[]){
    int flgx = -1, flgy = -1;
    Forr(i, 104, 0){
        if(x[i] != 0 && flgx == -1) flgx = i;
        if(y[i] != 0 && flgy == -1) flgy = i;
    }
    if(flgx == flgy){
        Forr(i, flgx, 0){
            if(x[i] > y[i]) return 1;
            else if(x[i] < y[i]) return -1;
        }
        return 0;
    }
    else return flgx > flgy ? 1 : -1;
}

int32_t main(){
    getAC();
    
    string s1, s2;
    cin >> s1 >> s2;
    int l1 = s1.length(), l2 = s2.length(), cnt = 0;
    Forr(i, l1-1, 0){
        a[cnt] = s1[i] - '0';
        cnt ++;
    }
    cnt = 0;
    Forr(i, l2-1, 0){
        b[cnt] = s2[i] - '0';
        cnt ++;
    }

    t[0] = 1;
    while(1){
        c[0] += 1;
        For(i, 0, 103){
            if(c[i] > 9){
                c[i+1] += (c[i]/10);
                c[i] %= 10;
            }
        }
        if(cmp(c, b) > 0){
            cout << "You will become a flying monkey!" << endl;
            break;
        }
        For(i, 0, 104){
            t[i] *= 2;
        }
        For(i, 0, 103){
            if(t[i] > 9){
                t[i+1] += (t[i]/10);
                t[i] %= 10;
            }
        }
        if(cmp(t, a) >= 0){
            cout << "Your wish is granted!" << endl;
            break;
        }
    }

    time();
    return 0;
}
