#include<bits/stdc++.h>
using namespace std;

bool comp(const vector<int>& a, const vector<int>& b){
    if(a[0] == b[0]) return a[1] < b[1];
    else return (a[0] < b[0]);
}

class FenwickTree{
    vector<int> bit;
    int n;
public:
    FenwickTree(int sz){
        n = sz;
        bit.resize(sz + 1, 0);
    }

    void update(int id, int val){
        while(id <= n){
            bit[id] += val;
            id += (id & -id);
        }
    }

    int get(int id){
        int sum = 0;
        while(id > 0){
            sum += bit[id];
            id -= (id & -id);
        }
        return sum;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> retailers;
    set<int> yvals;
    for(int i=0;i<n;i++){
        int u, v;
        cin >> u >> v;
        retailers.push_back({u, v});
        yvals.insert(v);
    }

    int q;
    cin >> q;
    vector<vector<int>> requests;
    for(int i=0;i<q;i++){
        int u, v;
        cin >> u >> v;
        yvals.insert(v);
        requests.push_back({u, v, i});
    }

    sort(retailers.begin(), retailers.end(), comp);
    sort(requests.begin(), requests.end(), comp);


    int idx = 1;
    unordered_map<int,int> um;
    for(auto x: yvals) um[x] = idx++;

    FenwickTree ft(um.size());
    vector<int> ans(q);
    
    idx = n-1;
    for(int i=q-1;i>=0;i--){
        int qx = requests[i][0], qy = requests[i][1];
        while(idx >= 0 && retailers[idx][0] >= qx){
            ft.update(um[retailers[idx][1]], 1);
            --idx;
        }
        ans[requests[i][2]] = ft.get(um.size()) - ft.get(um[qy] - 1);
    }

    for(auto& x: ans) cout << x << " ";
    cout << endl;

    return 0;
}
