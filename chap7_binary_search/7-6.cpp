#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;

int main(){
    cin >> n >> m;
    vector<int> a(n,0);

    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    int h=0;

    sort(a.begin(), a.end());

    h = a[0];

 
    int sum = 0;
    for(int h=a[n-1]; h>0; h--){
        vector<int> left(n,0);
        sum = 0;
        for(int j=0;j<n;j++){
            if(a[j]-h>0)
                left[j] = a[j]-h;
            else left[j] =0;
            sum += left[j];
            
        }
        if(sum >= m){
            cout<< h << '\n';
            return 0;
        }
        
    }
}