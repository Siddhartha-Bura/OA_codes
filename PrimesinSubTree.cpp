#include<bits/stdc++.h>
using namespace std;


int is_prime(int n){
    for(int i=2;i*i<=n;i++) if(n%i == 0) return 0;
    return 1;
}

int count_primes(int idx, vector<vector<int>>& tree, vector<int>& values, vector<int> &ans){
    int count = is_prime(values[idx]);
    for(int i=0;i<tree[idx].size();i++)
        count += count_primes(tree[idx][i], tree, values, ans);
    ans[idx] = count;
    return count;
}

vector<int> primeQuery(int n, vector<int> first, vector<int> second, vector<int> values, vector<int> queries){
    vector<vector<int>> tree(n);
    for(int i=0;i<n-1;i++) tree[first[i]-1].push_back(second[i]-1);
    vector<int> ans(n, 0);
    count_primes(0,tree, values, ans);
    vector<int> new_ans;
    for(auto i:queries) new_ans.push_back(ans[i-1]);
    return new_ans;
}


int main(){
    int n = 7;
    vector<int> first = {1,1,3,3,3,3};
    vector<int> second = {2,3,4,5,6,7};
    vector<int> values = {17,22,7,8,5,6,10};
    vector<int> queries = {1,2,3,4,5,6,7};
    for(auto i:primeQuery(n,first,second,values,queries))
        cout<<i<<" ";
}
