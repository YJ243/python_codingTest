#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
int main(){
    cin >> n;
    vector<int> a(n,0);
    
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    vector<int> sortedIndex(n,0);
    int answer = 0;
    int max_index = max_element(a.begin(), a.end())-a.begin();
    cout << max_index << '\n';
}