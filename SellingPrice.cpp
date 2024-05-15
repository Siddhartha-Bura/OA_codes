// Amazon allow sellers to create parent-child relationships for digital products to help customers find a version of a digital download they are looking for. You decide to start...

#include <bits/stdc++.h>
using namespace std;

vector<set<long>> solve(int idx, vector<vector<int>> &tree, vector<int> &a, vector<long> &ans){
    set<long> pos, neg;
    if(tree[idx].size() == 0){
        ans[idx] = 0;
        if(a[idx] < 0) neg.insert(a[idx]);
        else pos.insert(a[idx]);
        return {pos,neg};
    }
    for(int i=0;i<tree[idx].size();i++){
        vector<set<long>> v = solve(tree[idx][i],tree,a,ans);
        for(auto i:v[0]) pos.insert(i);
        for(auto i:v[1]) neg.insert(i);
    }
    if(a[idx] < 0) neg.insert(a[idx]);
    else pos.insert(a[idx]);
    while(pos.size() > 2) {pos.erase(pos.begin());}
    while(neg.size() > 2) {auto it = neg.end(); --it; neg.erase(it);}
  
    vector<long> v;
    if(pos.size() >= 1 and neg.size() >= 1){
        auto pit = pos.end();
        auto nit = neg.end();
        --pit;
        --nit;
        v.push_back((*pos.begin()) * (*nit));
        v.push_back((*pit) * (*neg.begin()));
    }  
    if(pos.size() >= 2){
        long tans = 1;
        for(auto ele:pos) tans *= ele;
        v.push_back(tans);
    }
    if(neg.size() >= 2){
        long tans = 1;
        for(auto ele:neg) tans *= ele;
        v.push_back(tans);
    }
    ans[idx] = *max_element(v.begin(),v.end());
    return {pos,neg};
}


vector<long> findPrice(int tree_nodes, vector<int> tree_from, vector<int> tree_to, vector<int> a){
    vector<vector<int>> tree(tree_nodes);
    for(int i=0;i<tree_nodes-1;i++) tree[tree_from[i]-1].push_back(tree_to[i]-1);
    vector<long> ans(tree_nodes, 0);
    solve(0,tree, a, ans);
    return ans;
}


int main() {
    vector<int> tree_from = {1,2,2,2,4}, tree_to = {2,3,4,5,6};
    int tree_nodes = 6;
    vector<int> a = {1,0,-1,-2,-3,9};
    vector<long> ans = findPrice(tree_nodes, tree_from, tree_to, a);
    for(auto i:ans) cout<<i<<" ";
    return 0;
}
