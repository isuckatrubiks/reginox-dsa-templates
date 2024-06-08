/*
Articulation points & bridges
Extended AC code to https://oj.vnoi.info/problem/graph_
 */
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 1e5+3;
ll n, m, low[maxn], num[maxn], cnt, cau, ch[maxn], kh;
bool khop[maxn];
vector<ll> adj[maxn], list_khop;
vector<pair<ll,ll>> list_cau;

void tarjan(ll u, ll p){
    num[u] = ++cnt, low[u] = num[u];
    for(auto v:adj[u]){
        if(v==p) continue;
        if(num[v] != 0) low[u] = min(low[u], num[v]);
        else{
           ++ch[u];
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= num[u]){
                khop[u] = true;
            }
            if(low[v] > num[u]){cau++; list_cau.push_back({v, u});}
        }
    }
//    if(is) cout << u << " " << child << "<- this\n";
}

int main(){
	if(fopen("test.inp","r")){
		freopen("test.inp","r",stdin);
		freopen("test.out","w",stdout);
	}
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(ll i = 1; i <= m; i++){
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(ll i = 1; i <= n; i++){
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }
    for(ll i = 1; i <= n; i++){
        if(num[i] == 0){
            tarjan(i, -1);
            if(ch[i] < 2) khop[i] = false;
        }
    }
    for(ll i = 1; i <= n; i++){
        if(khop[i]){
			kh++;
			list_khop.push_back(i);
        }
    }
    cout << kh << "\n";
    for(auto x:list_khop) cout << x << " ";
    cout << "\n" << cau << "\n";
    sort(list_cau.begin(), list_cau.end());
    for(auto x:list_cau) cout << x.first << " " << x.second << "\n";
    return 0;
}

/*
Output format:
#articulation points 
list of articulation points
#bridges
list of bridges
*/