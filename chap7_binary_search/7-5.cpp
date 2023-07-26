#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool BinarySearch(vector<int>& a, int start, int target, int end){
    if(start>end) return false;

    int mid = (start+end)/2;

    if (a[mid] == target) return true;
    else if(a[mid]<target) return BinarySearch(a, mid+1, target, end);
    else return BinarySearch(a, start, target, mid-1);
}


int n, target;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int m;
    cin >> m;
    vector<int> target(m);
    for(int i=0; i<m; i++){
        cin >> target[i];
    }
    for(int i=0; i<m; i++){
        bool check = BinarySearch(a, 0, target[i], n-1);
        if(!check){
            cout << "no"<< ' ';
        }
        else
        {
            cout<<"yes" << ' ';
        }
    }
    cout <<'\n';

    

}